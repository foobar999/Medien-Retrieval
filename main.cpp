#include <iostream>
#include <chrono>
#include "include/ImgReader.h"
#include "include/HSVConverter.h"
#include "include/HistogramCalculator.h"
#include "include/ImageSimilaritySorter.h"
#include "include/L1Distance.h"
#include "include/L2Distance.h"
#include "include/ChiSqDistance.h"
#include "include/HammingDistance.h"
#include "include/QueryResultDisplayer.h"
#include "include/MeanColorDistance.h"
#include "include/VarianceColorDistance.h"
#include "include/CrossDistance.h"
#include "include/CrosstalkCalculator.h"
#include "include/utils.h"
#include "include/JD.h"
#include "include/EMD.h"
#include "include/TamuraDistance.h"

using namespace cv;
using namespace std;
using namespace std::chrono;


int main(int argc, char **argv) {
    string dir = "data/2";
    vector<string> imgnames = ImgReader().get_filenames_from_dir(dir);
    vector<Mat> imgs = ImgReader().read_imgs_from_filenames(imgnames);
    cout << "read images: " << endl << imgnames << endl;

    vector<Mat> hsv_imgs = HSVConverter().convert_all(imgs);
    cout << "converted images to hsv space" << endl;

    Vec3f maxi(0, 0, 0);
    for(Mat hsv_img : hsv_imgs) {
        for(int i = 0; i < hsv_img.rows; i++) {
            for(int j = 0; j < hsv_img.cols; j++) {
                Vec3f ele = hsv_img.at<Vec3f>(i, j);
                maxi = Vec3f(max(maxi[0],ele[0]), max(maxi[1],ele[1]), max(maxi[2],ele[2]));
            }
        }
    }
    cout << "maximum hsv elements " << maxi << endl;

    Vec3i nbins(16, 3, 3);
    vector<Mat> hsv_hists;
    for(Mat hsv_img : hsv_imgs) {
        hsv_hists.push_back(HistogramCalculator().calc(hsv_img, nbins, HSVConverter::hsv_range));
    }
    cout << "calculated histograms" << endl;

    Mat crosstalk_mat = CrosstalkCalculator().calc(nbins, HSVConverter::hsv_range);

    vector<Mat> norm_hsv_hists;
    for(Mat &hist : hsv_hists) {
        norm_hsv_hists.push_back(HistogramCalculator().normalize(hist));
    }
    cout << "calculated normalized histograms" << endl;

    for(int img = 0; img < hsv_hists.size(); img++) {
        Mat &hist = hsv_hists[img];
        Mat &norm_hist = norm_hsv_hists[img];
        cout << "histogram of " << img << ":" << endl;
        /*
        for(int bin = 0; bin < hist.total(); bin++) {
            cout << "bin " << bin << ": abs " << hist.at<float>(0,bin) << " norm " << norm_hist.at<float>(0,bin) << endl;
        }
        */
        int bin_sum_abs = sum(hist)[0];
        float bin_sum_norm = sum(norm_hist)[0];
        cout << "bin sum abs " << bin_sum_abs << " expected " << hsv_imgs[img].total() << endl;
        cout << "bin sum norm " << bin_sum_norm << " expected 1" << endl;
    }

    vector<ImageData> imgs_data;
    for(int i = 0; i < imgs.size(); i++){
        imgs_data.emplace_back(imgs[i], hsv_imgs[i], hsv_hists[i], norm_hsv_hists[i]);
    }

    vector<ImageDistance*> distances = {
        new L1Distance(),
        new L2Distance(),
        new ChiSqDistance(),
        new HammingDistance(10),
        new MeanColorDistance(),
        new VarianceColorDistance(),
        new CrossDistance(crosstalk_mat),
        new JD(),
        new ::EMD(crosstalk_mat),
        new TamuraDistance(0, 4)
    };
    while(1) {
        cout << "Images:" << endl;
        for(int i = 0; i < imgnames.size(); i++) {
            cout << i << ": " << imgnames[i] << endl;
        }
        cout << endl << "Distances:" << endl;
        cout << "-1: all distances" << endl;
        for(int i = 0; i < distances.size(); i++) {
            cout << i << ": " << distances[i]->get_class_name() << endl;
        }
        int query_id;
        do {
            cout << "index of query image : ";
            cin >> query_id;
        } while(cin.fail() || query_id < 0 || query_id >= imgs.size());
        cout << "query image: " << imgnames[query_id] << endl;

        int distance_id;
        do {
            cout << "index of distance : ";
            cin >> distance_id;
            cout << cin.fail() << distance_id << " " << distances.size() << endl;
        } while(cin.fail() || distance_id < -1 || distance_id >= (int)distances.size());

        string winname;
        vector<ImageDistance*> dists_to_calc;
        if(distance_id > -1){
            dists_to_calc.push_back(distances[distance_id]);
            winname = "img " + imgnames[query_id] + ", " + distances[distance_id]->get_class_name();
        }
        else {
            dists_to_calc = distances;
            winname = "all distances";
        }

        vector<vector<Mat>> results_per_dist;
        for(ImageDistance *current_dist : dists_to_calc){
            cout << "image distance: " << current_dist->get_class_name() << endl;
            auto start_time = high_resolution_clock::now();
            vector<int> ids_sorted = ImageSimilaritySorter().sort_by_distance(query_id, imgs_data, *current_dist);
            auto end_time = high_resolution_clock::now();
            double elapsed_time = duration_cast<duration<double>>(end_time - start_time).count();
            cout << "duration " << elapsed_time << "sec" << endl;
            cout << "images similar to " << query_id << ": " << ids_sorted << endl;
            vector<Mat> imgs_sorted;
            for(int i : ids_sorted){
                imgs_sorted.push_back(imgs[i]);
            }
            results_per_dist.push_back(imgs_sorted);
        }
        QueryResultDisplayer().display(imgs[query_id], results_per_dist, winname);
    }

    return 0;
}
