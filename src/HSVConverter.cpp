#include "../include/HSVConverter.h"

using namespace std;
using namespace cv;

const Vec3f HSVConverter::ocv_hsv_range = Vec3f(180, 256, 256);
const Vec3f HSVConverter::hsv_range = Vec3f(360, 1, 1);

vector<Mat> HSVConverter::convert_all(vector<Mat> imgs){
    vector<Mat> hsv_imgs;
    Vec3f scale_vec;
    divide(hsv_range, ocv_hsv_range, scale_vec);
    for(Mat img : imgs){
        Mat hsv_img;
        cvtColor(img, hsv_img, CV_BGR2HSV);
        hsv_img.convertTo(hsv_img, CV_32FC3);
        for(int i = 0; i < hsv_img.rows; i++){
            for(int j = 0; j < hsv_img.cols; j++){
                Vec3f &ele = hsv_img.at<Vec3f>(i,j);
                ele = ele.mul(scale_vec);
            }
        }
        hsv_imgs.push_back(hsv_img);
    }
    return hsv_imgs;
}
