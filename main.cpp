#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImgReader.h"
#include "HSVConverter.h"
#include "HistogramCalculator.h"
#include "utils.h"

using namespace std;
using namespace cv;


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

    Vec3i nbins(16, 3, 3);
    HistogramCalculator hist_calc(nbins, HSVConverter::hsv_range);
    vector<Histogram> hsv_hists;
    for(Mat hsv_img : hsv_imgs) {
        Histogram hist = hist_calc.calc(hsv_img);
        hsv_hists.push_back(hist);
    }
    cout << "calculated histograms" << endl;

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

    for(int i = 0; i < imgs.size(); i++) {
        imshow(imgnames[i], imgs[i]);
    }
    waitKey();
    return 0;
}
