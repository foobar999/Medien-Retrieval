#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <opencv2/opencv.hpp>

class ImageData {
public:
    ImageData(cv::Mat img, cv::Mat abs_hist, cv::Mat norm_hist);
    cv::Mat img;
    cv::Mat abs_hist;
    cv::Mat norm_hist;
};

#endif // IMAGEDATA_H
