#include "HistogramCalculator.h"

using namespace std;
using namespace cv;

Histogram HistogramCalculator::calc(Mat hsv_img, const Vec3i &nbins, const Vec3f &range){
    vector<Mat> img_vec = {hsv_img};
    vector<int> use_all_channels = {0, 1, 2};
    Mat res;
    vector<int> nbins_vec = {nbins[0], nbins[1], nbins[2]};
    vector<float> ranges_vec = {0, range[0], 0, range[1], 0, range[2]};
    calcHist(img_vec, use_all_channels, Mat(), res, nbins_vec, ranges_vec);
    Histogram res_hist;
    res_hist.resize(nbins[0]);
    for(int i = 0; i < res_hist.size(); i++){
        res_hist[i].resize(nbins[1]);
        for(int j = 0; j < res_hist[i].size(); j++){
            res_hist[i][j].resize(nbins[2]);
            for(int k = 0; k < res_hist[i][j].size(); k++){
                res_hist[i][j][k] = res.at<float>(i, j, k);
            }
        }
    }
    return res_hist;
}
