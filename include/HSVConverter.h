#ifndef HSVCONVERTER_H
#define HSVCONVERTER_H

#include <vector>
#include <opencv2/opencv.hpp>

class HSVConverter {
public:
    // [180, 255, 255], [360, 1, 1]
    static const cv::Vec3f ocv_hsv_range, hsv_range;

    // converts from BGR to HSV
    // HSV ranges H [0,360], S[0,1], V[0,1]
    std::vector<cv::Mat> convert_all(std::vector<cv::Mat> imgs);

};

#endif // HSVCONVERTER_H
