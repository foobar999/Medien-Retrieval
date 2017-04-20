#include "ImgReader.h"

using namespace std;
using namespace cv;

vector<pair<Mat, string>> ImgReader::read_from_dir(string dirname) {
    vector<String> filenames;
    cv::glob(dirname, filenames);
    vector<pair<Mat,string>> imgs;
    for(String filename : filenames){
        imgs.push_back(make_pair(imread(filename, CV_LOAD_IMAGE_COLOR), filename));
    }
    return imgs;
}
