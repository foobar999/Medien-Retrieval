#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImgReader.h"
#include "HSVConverter.h"
#include "HistogramCalculator.h"

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
    /*
    vector<Mat> res;
    calcHist(hsv_imgs, vector<int>{0,1,2}, Mat(), res, vector<int>{16,3,3}, vector<float>{0,360,0,1,0,1});
    return 8;

    Mat hist2;
    Mat &img = hsv_imgs[2];
    calcHist(vector<Mat>{img}, vector<int>{0,1,2}, Mat(), hist2, vector<int>{16,3,3}, vector<float>{0,360,0,1,0,1});


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
    */


    Vec3i nbins(16, 3, 3);
    /*
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
    */
    HistogramCalculator hist_calc(nbins, HSVConverter::hsv_range);
    vector<Histogram> hsv_hists;
    for(Mat hsv_img : hsv_imgs) {
        Histogram hist = hist_calc.calc(hsv_img);
        hsv_hists.push_back(hist);
    }

    for(int img = 0; img < hsv_hists.size(); img++) {
        int bin_sum = 0;
        Histogram &hist = hsv_hists[img];
        cout << "histogram of " << img << ":" << endl;
        for(int i = 0; i < hist.size(); i++) {
            for(int j = 0; j < hist[i].size(); j++) {
                for(int k = 0; k < hist[i][j].size(); k++) {
                    Vec3i bin(i, j, k);
                    bin_sum += hist[i][j][k];
                    cout << "bin " << bin << ": " << hist[i][j][k] << " repr " << hist_calc.calc_repr(bin) << endl;
                }
            }
        }
        cout << "bin sum " << bin_sum << " expected " << hsv_imgs[img].total() << endl;
    }

    /*
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
    */


    for(int i = 0; i < imgs.size(); i++) {
        imshow(imgnames[i], imgs[i]);
    }
    waitKey();
    return 0;
}
