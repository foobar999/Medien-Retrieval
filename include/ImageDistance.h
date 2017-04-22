#ifndef IMAGEDISTANCE_H
#define IMAGEDISTANCE_H

#include <opencv2/opencv.hpp>

class ImageDistance {
public:
    virtual double calc(cv::Mat hist1, cv::Mat hist2) = 0;
    virtual std::string get_class_name() = 0;
    virtual ~ImageDistance() {}
};

#endif // IMAGEDISTANCE_H
