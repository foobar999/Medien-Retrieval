#include "MeanColorDistance.h"

using namespace std;
using namespace cv;


double MeanColorDistance::calc(const ImageData &dat1, const ImageData &dat2){
    Scalar mean_rgb1 = mean(dat1.rgb_img);
    Scalar mean_rgb2 = mean(dat2.rgb_img);
    return norm(mean_rgb1, mean_rgb2, NORM_L2);
}

string MeanColorDistance::get_class_name(){
    return "Mean Color Distance";
}
