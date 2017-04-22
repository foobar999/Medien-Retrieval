#include <iostream>
#include "ImgReader.h"
#include "HSVConverter.h"
#include "HistogramCalculator.h"
#include "ImageSimilaritySorter.h"
#include "L1Distance.h"
#include "L2Distance.h"
#include "ChiSqDistance.h"
#include "HammingDistance.h"
#include "QueryResultDisplayer.h"
#include "utils.h"

using namespace std;
using namespace cv;


int main(int argc, char **argv) {
    string dir = "data";
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
    HistogramCalculator hist_calc(nbins, HSVConverter::hsv_range);
    vector<Mat> hsv_hists;
    for(Mat hsv_img : hsv_imgs) {
        hsv_hists.push_back(hist_calc.calc(hsv_img));
    }
    cout << "calculated histograms" << endl;

    vector<Mat> norm_hsv_hists;
    for(Mat &hist : hsv_hists) {
        norm_hsv_hists.push_back(hist_calc.normalize(hist));
    }
    cout << "calculated normalized histograms" << endl;

    for(int img = 0; img < hsv_hists.size(); img++) {
        Mat &hist = hsv_hists[img];
        Mat &norm_hist = norm_hsv_hists[img];
        cout << "histogram of " << img << ":" << endl;
        /*
        for(int i = 0; i < nbins[0]; i++) {
            for(int j = 0; j < nbins[1]; j++) {
                for(int k = 0; k < nbins[2]; k++) {
                    Vec3i bin(i, j, k);
                    cout << "bin " << bin << ": abs " << hist.at<float>(i,j,k) << " norm " << norm_hist.at<float>(i,j,k);
                    cout << " (repr " << hist_calc.calc_repr(bin) << ")" << endl;
                }
            }
        }*/
        for(int bin = 0; bin < hist.total(); bin++) {
            cout << "bin " << bin << ": abs " << hist.at<float>(0,bin) << " norm " << norm_hist.at<float>(0,bin) << endl;
        }
        int bin_sum_abs = sum(hist)[0];
        float bin_sum_norm = sum(norm_hist)[0];
        cout << "bin sum abs " << bin_sum_abs << " expected " << hsv_imgs[img].total() << endl;
        cout << "bin sum norm " << bin_sum_norm << " expected 1" << endl;
    }

    vector<ImageDistance*> distances = {
        new L1Distance(),
        new L2Distance(),
        new ChiSqDistance(),
        new HammingDistance(0.5)
    };
    while(1) {
        cout << "Images:" << endl;
        for(int i = 0; i < imgnames.size(); i++) {
            cout << i << ": " << imgnames[i] << endl;
        }
        cout << endl << "Distances:" << endl;
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
        } while(cin.fail() || distance_id < 0 || distance_id >= distances.size());
        ImageDistance *dist = distances[distance_id];
        cout << "image distance: " << dist->get_class_name() << endl;

        vector<int> ids_sorted = ImageSimilaritySorter().sort_by_distance(query_id, norm_hsv_hists, *dist);
        cout << "images similar to " << query_id << ": " << ids_sorted << endl;

        vector<Mat> imgs_sorted;
        for(int i : ids_sorted){
            imgs_sorted.push_back(imgs[i]);
        }
        string winname = "img " + imgnames[query_id] + ", " + dist->get_class_name();
        QueryResultDisplayer().display(imgs[query_id], imgs_sorted, winname);
    }

    return 0;
}
