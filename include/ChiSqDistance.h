#ifndef CHISQDISTANCE_H
#define CHISQDISTANCE_H

#include "ImageDistance.h"


class ChiSqDistance : public ImageDistance {
public:
    double calc(const ImageData &dat1, const ImageData &dat2);
    std::string get_class_name();

};

#endif // CHISQDISTANCE_H
