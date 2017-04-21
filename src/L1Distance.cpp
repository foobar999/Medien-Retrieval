#include "L1Distance.h"

using namespace std;
using namespace cv;

double L1Distance::calc(Mat hist1, Mat hist2) const{
    return cv::norm(hist1, hist2, NORM_L2);
}
