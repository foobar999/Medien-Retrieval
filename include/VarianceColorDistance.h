#ifndef VARIANCECOLORDISTANCE_H
#define VARIANCECOLORDISTANCE_H

#include "ImageDistance.h"


class VarianceColorDistance : public ImageDistance {
public:
    double calc(const ImageData &dat1, const ImageData &dat2);
    std::string get_class_name();

};

#endif // VARIANCECOLORDISTANCE_H
