#ifndef L1DISTANCE_H
#define L1DISTANCE_H

#include "ImageDistance.h"


class L1Distance : public ImageDistance {
public:
    double calc(cv::Mat hist1, cv::Mat hist2) const;
};

#endif // L1DISTANCE_H
