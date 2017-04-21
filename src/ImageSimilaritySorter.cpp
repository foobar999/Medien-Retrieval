#include "ImageSimilaritySorter.h"

using namespace std;
using namespace cv;

vector<int> ImageSimilaritySorter::sort_by_distance(int query_id, const vector<Mat> &collection,
        const vector<Mat> &histograms, const ImageDistance &dist) {

    vector<double> dists;
    for(int i = 0; i < collection.size(); i++){
        dists.push_back(dist.calc(histograms[query_id], histograms[i]));
    }

    vector<int> res_indices(collection.size());
    std::iota(res_indices.begin(), res_indices.end(), 0);   // fülle vector mit 0, 1, 2, ..., collection.size()-1

    std::sort(res_indices.begin(), res_indices.end(), [&](const int &i1, const int &i2) {
        return dists[i1] < dists[i2];
    });
    return res_indices;
}
