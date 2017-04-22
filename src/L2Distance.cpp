#include "L2Distance.h"

using namespace std;
using namespace cv;

double L2Distance::calc(const ImageData &dat1, const ImageData &dat2){
    return cv::norm(dat1.norm_hist, dat2.norm_hist, NORM_L2);
}

string L2Distance::get_class_name(){
    return "L2Distance";
}
