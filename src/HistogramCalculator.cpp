#include "../include/HistogramCalculator.h"

using namespace std;
using namespace cv;

HistogramCalculator::HistogramCalculator(Vec3i nbins, Vec3f range){
    this->nbins = nbins;
    this->range = range;
}

Mat HistogramCalculator::calc(Mat hsv_img){
    vector<Mat> img_vec = {hsv_img};
    vector<int> use_all_channels = {0, 1, 2};
    Mat res;
    vector<int> nbins_vec = {nbins[0], nbins[1], nbins[2]};
    vector<float> ranges_vec = {0, range[0], 0, range[1], 0, range[2]};
    calcHist(img_vec, use_all_channels, Mat(), res, nbins_vec, ranges_vec);

    //dimensions of mat with dim 3+
    //cout << "(" << res.size[0] << "," << res.size[1] << "," << res.size[2] << ")" << endl;

    // convert 3D-histogram to 1D-histogram
    // of size 1 x (number of hist-elements) (row vector)
    Mat mat1d(1, res.total(), res.type(), (void*)res.data);
    return mat1d.clone();
}

Mat HistogramCalculator::normalize(Mat hist){
    Mat norm_hist;
    cv::normalize(hist, norm_hist, 1, 0, cv::NORM_L1);
    return norm_hist;
}


Vec3f HistogramCalculator::calc_repr(Vec3i bin){
    return Vec3f(bin[0]*range[0]/nbins[0], bin[1]*range[1]/nbins[1], bin[2]*range[2]/nbins[2]);
}

