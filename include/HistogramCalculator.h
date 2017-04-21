#ifndef HISTOGRAMCALCULATOR_H
#define HISTOGRAMCALCULATOR_H

#include <vector>
#include <opencv2/opencv.hpp>

typedef std::vector<std::vector<std::vector<int>>> Histogram;


class HistogramCalculator {
public:
    HistogramCalculator(cv::Vec3i nbins, cv::Vec3f range);
    Histogram calc(cv::Mat hsv_img);
    cv::Vec3f calc_repr(cv::Vec3i bin);
protected:
    cv::Vec3i nbins;
    cv::Vec3f range;
};

#endif // HISTOGRAMCALCULATOR_H
