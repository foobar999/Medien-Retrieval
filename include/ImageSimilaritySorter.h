#ifndef IMAGESIMILARITYSORTER_H
#define IMAGESIMILARITYSORTER_H

#include <vector>
#include "ImageDistance.h"
#include "utils.h"

class ImageSimilaritySorter {
public:
    std::vector<int> sort_by_distance(int query_id, const std::vector<cv::Mat> &histograms, ImageDistance &dist);
};

#endif // IMAGESIMILARITYSORTER_H
