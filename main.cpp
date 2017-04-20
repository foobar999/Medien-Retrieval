#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main(int argc, char **argv) {
    std::cout << "Welcome to OpenCV " << CV_VERSION << std::endl;
    Mat m(5, 10, CV_8UC1, Scalar(0));
    Mat mr1 = m.row(1);
    mr1.setTo(Scalar(1));
    Mat mc5 = m.col(5);
    mc5.setTo(Scalar(5));
    std::cout << "OpenCV Mat data:\n" << m << std::endl;
    return 0;
}
