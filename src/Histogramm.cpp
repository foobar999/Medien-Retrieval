#include "Histogramm.h"

using namespace std;
using namespace cv;

Histogramm::Histogramm(Vec3i nbins, Vec3f range) {
    this->nbins = nbins;
    this->range = range;
    bins.resize(nbins[0] * nbins[1] * nbins[2], 0);
}

void Histogramm::increment_bin(const Vec3f &color){
    bins[calc_bin(color)] += 1;
}

const vector<int>& Histogramm::get_bins(){
    return bins;
}

int Histogramm::calc_bin(const Vec3f &color){
    int s0 = nbins[1] * nbins[2] * floor(color[0] * nbins[0] / range[0]);
    int s1 = nbins[2] * floor(color[1] * nbins[1] / range[1]);
    int s2 = floor(color[2] * nbins[2] / range[2]);
    return s0 + s1 + s2;
}

Vec3f Histogramm::calc_repr(int bin){
    int i0 = bin % nbins[2];
    int i1 = bin % (nbins[1] * nbins[2]) / nbins[2];
    int i2 = bin % (nbins[0] * nbins[1] * nbins[2]) / (nbins[1] * nbins[2]);
    return Vec3f(i2*range[0]/nbins[0], i1*range[1]/nbins[1], i0*range[2]/nbins[2]);
}
