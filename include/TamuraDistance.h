#ifndef TAMURADISTANCE_H
#define TAMURADISTANCE_H

#include "ImageDistance.h"
#include "HistogramCalculator.h"

class TamuraDistance : public ImageDistance {
public:
	TamuraDistance(int kmin, int kmax) : kmin(kmin), kmax(kmax){}
	double calc(const ImageData &dat1, const ImageData &dat2);
	std::string get_class_name();
protected:
	int kmin, kmax;
    cv::Mat calc_granularity_sbest(cv::Mat bgr_img);
    cv::Mat translate_img(cv::Mat img, int x, int y);
};

#endif // TAMURADISTANCE_H
