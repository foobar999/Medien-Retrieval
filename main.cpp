#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImgReader.h"
#include "HSVConverter.h"
#include "Histogramm.h"

using namespace std;
using namespace cv;

template<typename T>
ostream& operator<<(ostream &os, const vector<T> &vec) {
    os << "[";
    for(int i = 0; i < vec.size(); i++) {
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
    for(Mat hsv_img : hsv_imgs) {
        for(int i = 0; i < hsv_img.rows; i++) {
            for(int j = 0; j < hsv_img.cols; j++) {
                maxs[0] = max(maxs[0], hsv_img.at<Vec3f>(i, j)[0]);
                maxs[1] = max(maxs[1], hsv_img.at<Vec3f>(i, j)[1]);
                maxs[2] = max(maxs[2], hsv_img.at<Vec3f>(i, j)[2]);
            }
        }
    }
    cout << "maximum hsv elements " << maxs << endl;

    Mat hist2;
    Mat &img = hsv_imgs[2];
    calcHist(vector<Mat>{img}, vector<int>{0,1,2}, Mat(), hist2, vector<int>{16,3,3}, vector<float>{0,360,0,1,0,1});
    /*
    int ch[] = {0,1,2};
    int siz[] = {16,3,3};
    float a[] = {0,360}, b[] = {0, 1};
    const float* rang[] = {a, b, b};
    calcHist(&hsv_imgs[0], 1, ch, Mat(), hist2, 3, siz, rang);
    cout << "hist 2 (img pixels " << hsv_imgs[0].total() << ")"<< endl;
    */
    int sum = 0;
    for (int i=0; i<16; i++) {
        for (int j=0; j<3; j++) {
            for (int k=0; k<3; k++) {
                int bin_count = hist2.at<float>(i, j, k);
                cout << "Value(" << i << ", " << j << ", " << k <<"): " << bin_count << endl;
                sum += bin_count;
            }
        }
    }

    cout << "bin sum " << sum << " number histogram pixels " << img.total() << endl;
    return 7;
    /*
    Histogramm h(Vec3i(16,3,3), Vec3f(360,1,1));
    for(int i = 0; i < 360; i++)
        for(float j = 0; j < 1; j += 0.01)
            for(float k = 0; k < 1; k += 0.01)
                h.increment_bin(Vec3f(i,j,k));
    for(int bin = 0; bin < h.get_bins().size(); bin++){
        cout << h.get_bins()[bin] << " hits for bin " << bin << " (repr " << h.calc_repr(bin) << "): " << endl;
    }
    return 6;
    */


    Vec3i nbins(16, 3, 3);
    vector<Histogramm> histograms;
    for(Mat hsv_img : hsv_imgs) {
        Histogramm hist(nbins, HSVConverter::hsv_range);
        for(int i = 0; i < hsv_img.rows; i++) {
            for(int j = 0; j < hsv_img.cols; j++) {
                hist.increment_bin(hsv_img.at<Vec3f>(i, j));
            }
        }
        histograms.push_back(hist);
    }

    for(int i = 0; i < histograms.size(); i++) {
        cout << "histogram nr. " << i << " (" << imgnames[i] << ")" << endl;
        for(int bin = 0; bin < histograms[i].get_bins().size(); bin++) {
            Histogramm &hist = histograms[i];
            cout << hist.get_bins()[bin] << " hits for bin " << bin;
            Vec3f repr = hist.calc_repr(bin);
            Mat_<Vec3f> repr_denorm(Vec3f(repr[0] / 2, repr[1] * 256, repr[2] * 256));
            Mat_<Vec3f> rgb;
            cvtColor(repr_denorm, rgb, CV_HSV2RGB);
            cout << " (rgb " << rgb << "): " << endl;
        }
    }



    for(int i = 0; i < imgs.size(); i++) {
        imshow(imgnames[i], imgs[i]);
    }
    waitKey();
    return 0;
}
