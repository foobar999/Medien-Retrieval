#ifndef HAMMINGDISTANCE_H
#define HAMMINGDISTANCE_H

#include "ImageDistance.h"


class HammingDistance : public ImageDistance {
public:
    HammingDistance(double thresh);
    double calc(cv::Mat hist1, cv::Mat hist2);
    std::string get_class_name();

protected:
    double thresh;
};

#endif // HAMMINGDISTANCE_H
