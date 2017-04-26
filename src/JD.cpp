#include "JD.h"
using namespace cv;
using namespace std;

double JD::calc(const ImageData &dat1, const ImageData &dat2){
    Mat hist1(1, dat1.norm_hist.total(), dat1.norm_hist.type(), (void*)dat1.norm_hist.data);
    Mat hist2(1, dat2.norm_hist.total(), dat2.norm_hist.type(), (void*)dat2.norm_hist.data);

    double sum = 0;
    for(int i = 0; i < hist1.total(); i++){
        float ele1 = hist1.at<float>(0, i);
        float ele2 = hist2.at<float>(0, i);
        float mean = (ele1 + ele2) / 2;
        cout << "ele1 " << ele1 << " ele2 " << ele2 << " res " << ele1 * std::log(ele1/mean) + ele2 * std::log(ele2/mean) << endl;

        double tempsum1 = ele1 * std::log(ele1/mean);
        double tempsum2 = ele2 * std::log(ele2/mean);

        //if(!isnan(tempsum1))
        //    cout << "HAIL!" << endl;


        if(isnan(tempsum1) == false)    // IEEE : f != f will be true only if f is NaN
            sum += tempsum1;
        if(isnan(tempsum2) == false)
            sum += tempsum2;
    }

    return sum;
}


string JD::get_class_name(){
    return "JD!";
}
