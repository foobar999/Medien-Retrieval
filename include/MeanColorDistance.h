#ifndef MEANCOLORDISTANCE_H
#define MEANCOLORDISTANCE_H

#include "ImageDistance.h"


class MeanColorDistance : public ImageDistance {
public:
    double calc(const ImageData &dat1, const ImageData &dat2);
    std::string get_class_name();

};

#endif // MEANCOLORDISTANCE_H
