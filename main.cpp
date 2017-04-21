#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImgReader.h"
#include "HSVConverter.h"
#include "HistogramCalculator.h"
#include "ImageSimilaritySorter.h"
#include "L1Distance.h"
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

    vector<float> maxs = {0, 0, 0};
    for(Mat hsv_img : hsv_imgs) {
        for(int i = 0; i < hsv_img.rows; i++) {
            for(int j = 0; j < hsv_img.cols; j++) {
                maxs[0] = max(maxs[0], hsv_img.at<Vec3f>(i, j)[0]);
                maxs[1] = max(maxs[1], hsv_img.at<Vec3f>(i, j)[1]);
                maxs[2] = max(maxs[2], hsv_img.at<Vec3f>(i, j)[2]);
            }
        }
    }
    cout << "maximum hsv elements " << maxs << endl;

    Vec3i nbins(16, 3, 3);
    HistogramCalculator hist_calc(nbins, HSVConverter::hsv_range);
    vector<Mat> hsv_hists;
    for(Mat hsv_img : hsv_imgs) {
        hsv_hists.push_back(hist_calc.calc(hsv_img));
    }
    cout << "calculated histograms" << endl;

    vector<Mat> norm_hsv_hists;
    for(Mat &hist : hsv_hists){
        norm_hsv_hists.push_back(hist_calc.normalize(hist));
    }
    cout << "calculated normalized histograms" << endl;

    for(int img = 0; img < hsv_hists.size(); img++) {
        Mat &hist = hsv_hists[img];
        Mat &norm_hist = norm_hsv_hists[img];
        cout << "histogram of " << img << ":" << endl;
        for(int i = 0; i < nbins[0]; i++) {
            for(int j = 0; j < nbins[1]; j++) {
                for(int k = 0; k < nbins[2]; k++) {
                    Vec3i bin(i, j, k);
                    cout << "bin " << bin << ": abs " << hist.at<float>(i,j,k) << " norm " << norm_hist.at<float>(i,j,k);
                    cout << " (repr " << hist_calc.calc_repr(bin) << ")" << endl;
                }
            }
        }
        int bin_sum_abs = sum(hist)[0];
        float bin_sum_norm = sum(norm_hist)[0];
        cout << "bin sum abs " << bin_sum_abs << " expected " << hsv_imgs[img].total() << endl;
        cout << "bin sum norm " << bin_sum_norm << " expected 1" << endl;
    }

    int query_id = 1;
    vector<int> ids_sorted = ImageSimilaritySorter().sort_by_distance(query_id, norm_hsv_hists, L1Distance());
    cout << "images similar to " << query_id << ": " << ids_sorted << endl;

    vector<Mat> thumbnails;
    for(int i : ids_sorted){
        Mat res;
        cv::resize(imgs[i], res, Size(200, 200));
        thumbnails.push_back(res);
    }
    Mat conc_thumbnails;
    hconcat(thumbnails, conc_thumbnails);

    imshow("most similar images", conc_thumbnails);
    //for(int i = 0; i < imgs.size(); i++) {
    //    imshow(imgnames[i], imgs[i]);
    //}

    waitKey();
    return 0;
}
