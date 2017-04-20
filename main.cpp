#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImgReader.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    string dir = "data";
    vector<string> imgnames = ImgReader().get_filenames_from_dir(dir);
    vector<Mat> imgs = ImgReader().read_imgs_from_filenames(imgnames);
    cout << "read " << imgs.size() << " images from " << dir << endl;

    vector<Mat> hsv_imgs;
    for(Mat img : imgs){
        Mat hsv_img;
        cvtColor(img, hsv_img, CV_BGR2HSV);
        hsv_imgs.push_back(hsv_img);
    }
    cout << "converted images to hsv space" << endl;

    for(Mat hsv_img : hsv_imgs){
        for(int i = 0; i < hsv_img.rows; i++){
            for(int j = 0; j < hsv_img.cols; j++){
               cout << hsv_img.at<Vec3b>(i, j) << endl;
            }
        }
    }

    for(int i = 0; i < imgs.size(); i++){
        imshow(imgnames[i], imgs[i]);
    }
    waitKey();
    return 0;
}
