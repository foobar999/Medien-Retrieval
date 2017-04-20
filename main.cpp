#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImgReader.h"

using namespace std;
using namespace cv;

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
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

    for(int img = 0; img < imgs.size(); img++){
        for(int i = 0; i < imgs[img].rows; i++){
            for(int j = 0; j < imgs[img].cols; j++){
               cout << imgs[img].at<Vec3b>(i, j) << " " << hsv_imgs[img].at<Vec3f>(i,j) << endl;
            }
        }

    }

    for(int i = 0; i < imgs.size(); i++){
        imshow(imgnames[i], imgs[i]);
    }
    waitKey();
    return 0;
}
