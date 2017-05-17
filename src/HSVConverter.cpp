#include "../include/HSVConverter.h"

using namespace std;
using namespace cv;

const Vec3f HSVConverter::ocv_hsv_range = Vec3f(180, 256, 256);
const Vec3f HSVConverter::hsv_range = Vec3f(360, 1, 1);

vector<Mat> HSVConverter::convert_all(vector<Mat> imgs){
    vector<Mat> hsv_imgs;
    Vec3f scale_vec;
    divide(hsv_range, ocv_hsv_range, scale_vec);
    Scalar scale_scalar = scale_vec;
    cout << "scaling by " << scale_scalar << endl;
    for(Mat img : imgs){
        Mat hsv_img;
        cvtColor(img, hsv_img, CV_BGR2HSV);
        hsv_img.convertTo(hsv_img, CV_32FC3);
        multiply(hsv_img, scale_scalar, hsv_img);
        hsv_imgs.push_back(hsv_img);
    }
    return hsv_imgs;
}
