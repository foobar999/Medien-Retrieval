#include "HammingDistance.h"

using namespace cv;
using namespace std;

HammingDistance::HammingDistance(double thresh){
    this->thresh = thresh;
}

double HammingDistance::calc(Mat hist1, Mat hist2){
    Mat diff;
    absdiff(hist1, hist2, diff);
    Mat thresh_h1 = hist1 > thresh;
    Mat thresh_h2 = hist2 > thresh;
    Mat thresh_diff = diff > thresh;
    int denom = countNonZero(thresh_h1) * countNonZero(thresh_h2);
    return denom == 0 ? std::numeric_limits<double>::infinity() : countNonZero(thresh_diff) / denom;
}

string HammingDistance::get_class_name(){
    return "Hamming-Distance";
}
