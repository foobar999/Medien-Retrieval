#include "EMD.h"

using namespace cv;
using namespace std;

EMD::EMD(Mat crosstalk_mat){
    this->crosstalk_mat = crosstalk_mat;
}

double EMD::calc(const ImageData &dat1, const ImageData &dat2){
    Mat h1 = dat1.norm_hist, h2 = dat2.norm_hist;
    Mat h1_1d(h1.total(), 1, h1.type(), (void*)h1.data);
    Mat h2_1d(h2.total(), 1, h2.type(), (void*)h2.data);
    cout << "emd sizes: h1 " << h1_1d.size() << " h2 " << h2_1d.size() << " crosstalk " << crosstalk_mat.size() << endl;
    double dist = cv::EMD(h1_1d, h2_1d, DIST_USER, 1 - crosstalk_mat);
    return dist;
}

string EMD::get_class_name(){
    return "Earth Movers Distance";
}
