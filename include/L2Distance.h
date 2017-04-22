#ifndef L2DISTANCE_H
#define L2DISTANCE_H

#include "ImageDistance.h"


class L2Distance : public ImageDistance {
public:
    double calc(const ImageData &dat1, const ImageData &dat2);
    std::string get_class_name();
};

#endif // L2DISTANCE_H
