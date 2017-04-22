#ifndef HAMMINGDISTANCE_H
#define HAMMINGDISTANCE_H

#include "ImageDistance.h"


class HammingDistance : public ImageDistance {
public:
    HammingDistance(double thresh);
    double calc(const ImageData &dat1, const ImageData &dat2);
    std::string get_class_name();

protected:
    double thresh;
};

#endif // HAMMINGDISTANCE_H
