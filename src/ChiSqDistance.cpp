#include "../include/ChiSqDistance.h"

using namespace cv;
using namespace std;

double ChiSqDistance::calc(const ImageData &dat1, const ImageData &dat2){
    return compareHist(dat1.norm_hist, dat2.norm_hist, HISTCMP_CHISQR_ALT);
}

string ChiSqDistance::get_class_name(){
    return "Chi-Squared-Distance";
}
