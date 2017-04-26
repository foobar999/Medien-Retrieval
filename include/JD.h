#ifndef JD_H
#define JD_H

#include <cmath>
#include "../include/ImageDistance.h"

class JD : public ImageDistance
{
    public:
        double calc(const ImageData &dat1, const ImageData &dat2);
        std::string get_class_name();
    protected:
    private:
};

#endif // JD_H
