#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImgReader.h"

using namespace std;
using namespace cv;

template<typename T>
ostream& operator<<(ostream &os, const vector<T> &vec){
    os << "[";
    for(int i = 0; i < vec.size(); i++){
        os << vec[i] << (i == vec.size()-1 ? "" : ", ");
    }
    os << "]";
    return os;
}

int main(int argc, char **argv) {
    string dir = "data";
    vector<string> imgnames = ImgReader().get_filenames_from_dir(dir);
    vector<Mat> imgs = ImgReader().read_imgs_from_filenames(imgnames);
    cout << "read " << imgs.size() << " images from " << dir << endl;

    vector<Mat> hsv_imgs;
    for(Mat img : imgs){
        Mat hsv_img;
        // OpenCV HSV ranges H [0,180], S [0,255], V [0,255]
        cvtColor(img, hsv_img, CV_BGR2HSV);
        hsv_img.convertTo(hsv_img, CV_32FC3);
        Vec3f scale_vec(360/180, 1.0/255, 1.0/255);
        // converting to H [0,360], S[0,1], V[0,1]
        for(int i = 0; i < hsv_img.rows; i++){
            for(int j = 0; j < hsv_img.cols; j++){
                Vec3f &ele = hsv_img.at<Vec3f>(i,j);
                ele = ele.mul(scale_vec);
            }
        }
        hsv_imgs.push_back(hsv_img);
    }
    cout << "converted images to hsv space" << endl;

    vector<float> maxs = {0, 0, 0};
    for(Mat hsv_img : hsv_imgs){
        for(int i = 0; i < hsv_img.rows; i++){
            for(int j = 0; j < hsv_img.cols; j++){
               maxs[0] = max(maxs[0], hsv_img.at<Vec3f>(i, j)[0]);
               maxs[1] = max(maxs[1], hsv_img.at<Vec3f>(i, j)[1]);
               maxs[2] = max(maxs[2], hsv_img.at<Vec3f>(i, j)[2]);
            }
        }
    }
    cout << "maximum hsv  elements " << maxs << endl;

    for(int i = 0; i < imgs.size(); i++){
        imshow(imgnames[i], imgs[i]);
    }
    waitKey();
    return 0;
}
