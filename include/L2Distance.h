#ifndef L2DISTANCE_H
#define L2DISTANCE_H

#include "ImageDistance.h"


class L2Distance : public ImageDistance {
public:
    double calc(cv::Mat hist1, cv::Mat hist2) const;
    std::string get_class_name();
};

#endif // L2DISTANCE_H
