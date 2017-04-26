#include "../include/ChiSqDistance.h"

using namespace cv;
using namespace std;

double ChiSqDistance::calc(const ImageData &dat1, const ImageData &dat2){
    return compareHist(dat1.abs_hist, dat2.abs_hist, HISTCMP_CHISQR);
}

string ChiSqDistance::get_class_name(){
    return "Chi-Squared-Distance";
}
