#include "../include/L1Distance.h"

using namespace std;
using namespace cv;

double L1Distance::calc(const ImageData &dat1, const ImageData &dat2){
    return cv::norm(dat1.norm_hist, dat2.norm_hist, NORM_L1);
}

string L1Distance::get_class_name(){
    return "L1Distance";
}
