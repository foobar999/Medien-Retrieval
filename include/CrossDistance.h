#ifndef CROSSDISTANCE_H
#define CROSSDISTANCE_H

#include "../include/ImageDistance.h"


class CrossDistance : public ImageDistance {
public:
    CrossDistance(cv::Mat crosstalk_mat);
    double calc(const ImageData &dat1, const ImageData &dat2);
    std::string get_class_name();

protected:
    cv::Mat crosstalk_mat;
};

#endif // CROSSDISTANCE_H
