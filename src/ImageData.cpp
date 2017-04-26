#include "../include/ImageData.h"

ImageData::ImageData(cv::Mat rgb_img, cv::Mat hsv_img, cv::Mat abs_hist, cv::Mat norm_hist){
    this->rgb_img = rgb_img;
    this->hsv_img = hsv_img;
    this->abs_hist = abs_hist;
    this->norm_hist = norm_hist;
}
