#include "../include/VarianceColorDistance.h"

using namespace cv;
using namespace std;

double VarianceColorDistance::calc(const ImageData &dat1, const ImageData &dat2){
    Scalar stddev1, stddev2;
    meanStdDev(dat1.rgb_img, noArray(), stddev1);
    meanStdDev(dat2.rgb_img, noArray(), stddev2);
    // TODO standard deviation sufficient?
    Scalar var1, var2;
    cv::pow(stddev1, 2, var1);
    cv::pow(stddev2, 2, var2);
    return norm(var1, var2, NORM_L2);
}

string VarianceColorDistance::get_class_name(){
    return "Variance Color Distance";
}
