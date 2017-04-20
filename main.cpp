#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImgReader.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    vector<pair<Mat,string>> images = ImgReader().read_from_dir("data");
    for(pair<Mat,string> img : images){
        imshow(img.second, img.first);
    }
    waitKey();
    return 0;
}
