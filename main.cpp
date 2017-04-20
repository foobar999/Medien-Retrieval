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

// liefert zur Farbe color den bin gemäß der Aufteilung durch nbins und range
// die Aufteilung wir bestimmt durch nbins (Anzahl der Bins je Dimension)
// und range (Wertebereich je Dimension)
int calc_bin(Vec3f color, Vec3i nbins, Vec3f range){
    int s0 = nbins[1] * nbins[2] * floor(color[0] * nbins[0] / range[0]);
    int s1 = nbins[2] * floor(color[1] * nbins[1] / range[1]);
    int s2 = floor(color[2] * nbins[2] / range[2]);
    return s0 + s1 + s2;
}

// liefert die kleinste Stellvertreterfarbe des Bins bin
Vec3f calc_repr(int bin, Vec3i nbins, Vec3f range){
    int i0 = bin % nbins[2];
    int i1 = bin % (nbins[1] * nbins[2]) / nbins[2];
    int i2 = bin % (nbins[0] * nbins[1] * nbins[2]) / (nbins[1] * nbins[2]);
    return Vec3f(i2*range[0]/nbins[0], i1*range[1]/nbins[1], i0*range[2]/nbins[2]);
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
    cout << "maximum hsv elements " << maxs << endl;

    typedef Vec<int, 16*3*3> Histogramm;
    Histogramm hist;
    for(int i = 0; i < 360; i++)
        for(float j = 0; j < 1; j += 0.01)
            for(float k = 0; k < 1; k += 0.01)
                hist[calc_bin(Vec3f(i,j,k), Vec3i(16,3,3), Vec3f(360,1,1))] += 1;

    cout << "histogramm: " << endl;
    for(int i = 0; i < hist.rows; i++){
        cout << i << ": " << hist[i] << " (" << calc_repr(i, Vec3i(16,3,3), Vec3f(360,1,1)) << ")" << endl;
    }

    for(int i = 0; i < imgs.size(); i++){
        imshow(imgnames[i], imgs[i]);
    }
    waitKey();
    return 0;
}
