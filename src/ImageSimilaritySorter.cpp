#include "ImageSimilaritySorter.h"

using namespace std;
using namespace cv;

vector<int> ImageSimilaritySorter::sort_by_distance(int query_id, const vector<Mat> &histograms, ImageDistance &dist) {

    vector<double> dists;
    for(int i = 0; i < histograms.size(); i++){
        dists.push_back(dist.calc(histograms[query_id], histograms[i]));
    }
    cout << "dists:" << endl << dists << endl;
    vector<int> res_indices(histograms.size());
    std::iota(res_indices.begin(), res_indices.end(), 0);   // fülle vector mit 0, 1, 2, ..., collection.size()-1

    std::sort(res_indices.begin(), res_indices.end(), [&](const int &i1, const int &i2) {
        return dists[i1] < dists[i2];
    });
    cout << "result distances:" << endl;
    for(int i = 0; i < res_indices.size(); i++){
        cout << dists[res_indices[i]] << (i == res_indices.size()-1 ? "\n" : ", ");
    }
    return res_indices;
}
