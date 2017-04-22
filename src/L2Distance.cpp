#include "L2Distance.h"

using namespace std;
using namespace cv;

double L2Distance::calc(Mat hist1, Mat hist2){
    return cv::norm(hist1, hist2, NORM_L2);
}

string L2Distance::get_class_name(){
    return "L2Distance";
}
