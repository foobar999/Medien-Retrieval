#include "../include/HammingDistance.h"

using namespace cv;
using namespace std;

HammingDistance::HammingDistance(int thresh){
    this->thresh = thresh;
}

double HammingDistance::calc(const ImageData &dat1, const ImageData &dat2){
    Mat thresh_h1 = dat1.abs_hist > thresh;
    Mat thresh_h2 = dat2.abs_hist > thresh;
    Mat thresh_diff;
    bitwise_xor(thresh_h1, thresh_h2, thresh_diff);
    double denom = countNonZero(thresh_h1) * countNonZero(thresh_h2);
    return denom == 0 ? std::numeric_limits<double>::infinity() : countNonZero(thresh_diff) / denom;
}

string HammingDistance::get_class_name(){
    return "Hamming-Distance";
}
