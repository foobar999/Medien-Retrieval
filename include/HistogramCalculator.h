#ifndef HISTOGRAMCALCULATOR_H
#define HISTOGRAMCALCULATOR_H

#include <vector>
#include <opencv2/opencv.hpp>

class HistogramCalculator {
public:
    cv::Mat calc(cv::Mat hsv_img, cv::Vec3i nbins, cv::Vec3f range);
    cv::Mat calc_1d_hist(cv::Mat values, int nbins, cv::Vec2f range);
    cv::Mat normalize(cv::Mat hist);
protected:
    cv::Vec3i nbins;
    cv::Vec3f range;
};

#endif // HISTOGRAMCALCULATOR_H
