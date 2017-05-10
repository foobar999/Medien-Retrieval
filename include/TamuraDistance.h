#ifndef TAMURADISTANCE_H
#define TAMURADISTANCE_H

#include "ImageDistance.h"


class TamuraDistance : public ImageDistance {
public:
	TamuraDistance(int kmin, int kmax) : kmin(kmin), kmax(kmax){}
	double calc(const ImageData &dat1, const ImageData &dat2);
	std::string get_class_name();
protected:
	int kmin, kmax;

};

#endif // TAMURADISTANCE_H
