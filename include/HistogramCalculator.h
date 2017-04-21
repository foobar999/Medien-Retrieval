#ifndef HISTOGRAMCALCULATOR_H
#define HISTOGRAMCALCULATOR_H

#include <vector>
#include <opencv2/opencv.hpp>

typedef std::vector<std::vector<std::vector<int>>> Histogram;


class HistogramCalculator {
public:
    Histogram calc(cv::Mat hsv_img, const cv::Vec3i &nbins, const cv::Vec3f &range);

};

#endif // HISTOGRAMCALCULATOR_H
