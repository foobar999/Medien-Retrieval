#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImgReader.h"
#include "HSVConverter.h"
#include "Histogramm.h"

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
    cout << "read images: " << endl << imgnames << endl;

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
    cout << "maximum hsv elements " << maxs << endl;

    //Vec3f err(340, 1, 0.0117647);
    //cout << "binnn " << Histogramm (Vec3i(16, 3, 3), HSVConverter::hsv_range).calc_bin(err) << endl;

    Vec3i nbins(16, 3, 3);
    vector<Histogramm> histograms;
    histograms.reserve(imgs.size());
    for(Mat hsv_img : hsv_imgs){
        cout << "a" << endl;
        Histogramm hist(nbins, HSVConverter::hsv_range);
        cout << "b" << endl;
        for(int i = 0; i < hsv_img.rows; i++){
            for(int j = 0; j < hsv_img.cols; j++){
                hist.increment_bin(hsv_img.at<Vec3f>(i, j));
            }
        }
        histograms.push_back(hist);
        cout << "c" << endl;
    }

    cout << "histograms of images: " << endl;
    for(int i = 0; i < histograms.size(); i++){
        cout << i << ": " << histograms[i].get_bins() << endl;
    }



    for(int i = 0; i < imgs.size(); i++){
        imshow(imgnames[i], imgs[i]);
    }
    waitKey();
    return 0;
}
