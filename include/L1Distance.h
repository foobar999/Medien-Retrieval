#ifndef L1DISTANCE_H
#define L1DISTANCE_H

#include "ImageDistance.h"


class L1Distance : public ImageDistance {
public:
    double calc(const ImageData &dat1, const ImageData &dat2);
    std::string get_class_name();
};

#endif // L1DISTANCE_H
