#ifndef HAMMINGDISTANCE_H
#define HAMMINGDISTANCE_H

#include "ImageDistance.h"


class HammingDistance : public ImageDistance {
public:
    HammingDistance(int thresh);
    double calc(const ImageData &dat1, const ImageData &dat2);
    std::string get_class_name();

protected:
    int thresh;
};

#endif // HAMMINGDISTANCE_H
