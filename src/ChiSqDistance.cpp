#include "ChiSqDistance.h"

using namespace cv;
using namespace std;

double ChiSqDistance::calc(Mat hist1, Mat hist2){
    return compareHist(hist1, hist2, HISTCMP_CHISQR);
}

string ChiSqDistance::get_class_name(){
    return "Chi-Squared-Distance";
}
