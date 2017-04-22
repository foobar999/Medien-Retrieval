#include "ImageData.h"

ImageData::ImageData(cv::Mat img, cv::Mat abs_hist, cv::Mat norm_hist){
    this->img = img;
    this->abs_hist = abs_hist;
    this->norm_hist = norm_hist;
}
