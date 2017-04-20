#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImgReader.h"
#include "HSVConverter.h"

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

    vector<Mat> hsv_imgs = HSVConverter().convert_all(imgs);
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
