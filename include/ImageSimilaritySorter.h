#ifndef IMAGESIMILARITYSORTER_H
#define IMAGESIMILARITYSORTER_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "ImageDistance.h"

class ImageSimilaritySorter {
public:
    std::vector<int> sort_by_distance(int query_id, const std::vector<cv::Mat> &histograms, const ImageDistance &dist);
};

#endif // IMAGESIMILARITYSORTER_H
