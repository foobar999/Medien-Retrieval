#ifndef HISTOGRAMCALCULATOR_H
#define HISTOGRAMCALCULATOR_H

#include <vector>
#include <opencv2/opencv.hpp>

class HistogramCalculator {
public:
    HistogramCalculator(cv::Vec3i nbins, cv::Vec3f range);
    cv::Mat calc(cv::Mat hsv_img);

    cv::Mat normalize(cv::Mat hist);
    cv::Vec3f calc_repr(cv::Vec3i bin);
protected:
    cv::Vec3i nbins;
    cv::Vec3f range;
};

#endif // HISTOGRAMCALCULATOR_H
