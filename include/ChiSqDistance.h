#ifndef CHISQDISTANCE_H
#define CHISQDISTANCE_H

#include "ImageDistance.h"


class ChiSqDistance : public ImageDistance {
public:
    double calc(cv::Mat hist1, cv::Mat hist2);
    std::string get_class_name();

};

#endif // CHISQDISTANCE_H
