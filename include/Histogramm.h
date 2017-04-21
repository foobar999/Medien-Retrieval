#ifndef HISTOGRAMM_H
#define HISTOGRAMM_H

#include <vector>
#include <opencv2/core.hpp>
#include <iostream>

class Histogramm {
public:
    Histogramm(cv::Vec3i nbins, cv::Vec3f range);
    void increment_bin(const cv::Vec3f &color);
    const std::vector<int>& get_bins();

    // liefert die kleinste Stellvertreterfarbe des Bins bin
    cv::Vec3f calc_repr(int bin);

    // liefert zur Farbe color den bin gem‰ﬂ der Aufteilung durch nbins und range
    // die Aufteilung wir bestimmt durch nbins (Anzahl der Bins je Dimension)
    // und range (Wertebereich je Dimension)
    int calc_bin(const cv::Vec3f &color);

protected:
    std::vector<int> bins;
    cv::Vec3i nbins;
    cv::Vec3f range;
};

#endif // HISTOGRAMM_H
