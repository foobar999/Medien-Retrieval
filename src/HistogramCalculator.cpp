#include "../include/HistogramCalculator.h"

using namespace std;
using namespace cv;

Mat HistogramCalculator::calc(Mat hsv_img, Vec3i nbins, Vec3f range){
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
    //Mat mat1d(1, res.total(), res.type(), (void*)res.data);
    //return mat1d.clone();
    return res;
}

Mat HistogramCalculator::calc_1d_hist(Mat values, int nbins, Vec2f range){
    vector<Mat> values_vec = {values};
    vector<int> use_1_channel = {0};
    Mat res;
    vector<int> nbins_vec = {nbins};
    vector<float> ranges_vec = {range[0], range[1]};
    calcHist(values_vec, use_1_channel, Mat(), res, nbins_vec, ranges_vec);

    /*
    //vector<Mat> values_vec = {values};
    int nchannels[] = {0};
    Mat res;
    const float range[] = {0, maxval};
    const float *x[] = {range};
    calcHist(&values, 1, nchannels, Mat(), res, 1, &nbins, x);
    return res;
    */
    return res.t();
}

Mat HistogramCalculator::normalize(Mat hist){
    Mat norm_hist;
    cv::normalize(hist, norm_hist, 1, 0, cv::NORM_L1);
    return norm_hist;
}

