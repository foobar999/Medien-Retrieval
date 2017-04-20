#include "ImgReader.h"

using namespace std;
using namespace cv;

vector<string> ImgReader::get_filenames_from_dir(string dirname){
    vector<String> filenames;
    cv::glob(dirname, filenames);
    return vector<string>(filenames.begin(), filenames.end());
}

vector<Mat> ImgReader::read_imgs_from_filenames(const vector<string> &filenames) {
    vector<Mat> imgs;
    for(string filename : filenames){
        imgs.push_back(imread(filename, CV_LOAD_IMAGE_COLOR));
    }
    return imgs;
}
