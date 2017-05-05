#ifndef EMD_H
#define EMD_H

#include "ImageDistance.h"


class EMD : public ImageDistance {
public:
    EMD(cv::Mat crosstalk_mat);
    double calc(const ImageData &dat1, const ImageData &dat2);
    std::string get_class_name();
protected:
    cv::Mat crosstalk_mat;
};
#endif // EMD_H
