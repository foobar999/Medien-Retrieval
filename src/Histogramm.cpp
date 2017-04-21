#include "Histogramm.h"

using namespace std;
using namespace cv;

Histogramm::Histogramm(Vec3i nbins, Vec3f range) {
    this->nbins = nbins;
    this->range = range;
    bins.resize(nbins[0] * nbins[1] * nbins[2], 0);
}

void Histogramm::increment_bin(const Vec3f &color){
    int b = calc_bin(color);
    if (b < 0 || b >= bins.size())cout << "FEHLR " << color << " : " << b << endl;
    bins[calc_bin(color)] += 1;
}

const vector<int>& Histogramm::get_bins(){
    return bins;
}

int Histogramm::calc_bin(const Vec3f &color){
    /*int s0 = nbins[1] * nbins[2] * color[0] * floor(nbins[0] / range[0]);
    int s1 = nbins[2] * color[1] * floor(nbins[1] / range[1]);
    int s2 = color[2] * floor(nbins[2] / range[2]);
    return s0 + s1 + s2;*/
    int i2 = color[0] * floor(nbins[0] / range[0]);
    int i1 = color[1] * floor(nbins[1] / range[1]);
    int i0 = color[2] * floor(nbins[2] / range[2]);
    return i2 * nbins[1] * nbins[2] + i1 * nbins[2] + i0;
}

Vec3f Histogramm::calc_repr(int bin){
    int i0 = bin % nbins[2];
    int i1 = bin % (nbins[1] * nbins[2]) / nbins[2];
    int i2 = bin % (nbins[0] * nbins[1] * nbins[2]) / (nbins[1] * nbins[2]);
    return Vec3f(i2*range[0]/nbins[0], i1*range[1]/nbins[1], i0*range[2]/nbins[2]);
}
