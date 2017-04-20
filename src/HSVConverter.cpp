#include "HSVConverter.h"

using namespace std;
using namespace cv;

vector<Mat> HSVConverter::convert_all(vector<Mat> imgs){
    vector<Mat> hsv_imgs;
    for(Mat img : imgs){
        Mat hsv_img;
        // OpenCV HSV ranges: H [0,180], S [0,255], V [0,255]
        cvtColor(img, hsv_img, CV_BGR2HSV);
        hsv_img.convertTo(hsv_img, CV_32FC3);
        Vec3f scale_vec(360/180, 1.0/255, 1.0/255);
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
