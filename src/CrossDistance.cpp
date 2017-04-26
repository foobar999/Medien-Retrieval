#include "../include/CrossDistance.h"

using namespace cv;
using namespace std;


CrossDistance::CrossDistance(Mat crosstalk_mat){
    this->crosstalk_mat = crosstalk_mat;
}

double CrossDistance::calc(const ImageData &dat1, const ImageData &dat2){

    Mat hist1(1, dat1.abs_hist.total(), dat1.abs_hist.type(), (void*)dat1.abs_hist.data);
    Mat hist2(1, dat2.abs_hist.total(), dat2.abs_hist.type(), (void*)dat2.abs_hist.data);
    return Mahalanobis(hist1, hist2, crosstalk_mat);
    //return mat1d.clone();
}


string CrossDistance::get_class_name(){
    return "Cross Distance";
}
