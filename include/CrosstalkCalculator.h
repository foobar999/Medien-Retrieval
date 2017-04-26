#ifndef CROSSTALKCALCULATOR_H
#define CROSSTALKCALCULATOR_H

#include <opencv2/opencv.hpp>

class CrosstalkCalculator
{
public:
    cv::Mat calc(cv::Vec3i nbins, cv::Vec3f range);
protected:
    cv::Vec3f calc_repr(cv::Vec3i bin, cv::Vec3i nbins, cv::Vec3f range);
};

#endif // CROSSTALKCALCULATOR_H
