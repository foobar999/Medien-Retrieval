#ifndef IMAGEDISTANCE_H
#define IMAGEDISTANCE_H

#include <opencv2/opencv.hpp>
#include "ImageData.h"

class ImageDistance {
public:
    virtual double calc(const ImageData &dat1, const ImageData &dat2) = 0;
    virtual std::string get_class_name() = 0;
    virtual ~ImageDistance() {}
};

#endif // IMAGEDISTANCE_H
