#include "../include/CrosstalkCalculator.h"


using namespace cv;
using namespace std;

Mat CrosstalkCalculator::calc(Vec3i nbins, Vec3f range){
    vector<Vec3f> centroids;
    for(int i = 0; i < nbins[0]; i++){
        for(int j = 0; j < nbins[1]; j++){
            for(int k = 0; k < nbins[2]; k++){
                Vec3i bin(i, j, k);
                Vec3f sum(0,0,0);
                vector<Vec3i> offsets = {Vec3i(0,0,0), Vec3i(0,0,1), Vec3i(0,1,0), Vec3i(0,1,1), Vec3i(1,0,0), Vec3i(1,0,1), Vec3i(1,1,0), Vec3i(1,1,1)};
                for(Vec3i offset : offsets){
                    sum += calc_repr(bin + offset, nbins, range);
                }
                cv::divide(sum, offsets.size(), sum);
                centroids.push_back(sum);
                cout << "bin: " << bin << " color: " << calc_repr(bin, nbins, range) << " sum " << sum << endl;
    }}}
    Mat res(centroids.size(), centroids.size(), CV_32F);
    double dmax = 0;
    for(int i = 0; i < centroids.size(); i++){
        for(int j = 0; j < centroids.size(); j++){
//            res.at<float>(i, j) = cv::norm(sums[i], sums[j]);
            double dist = d_cyl(centroids[i], centroids[j]);
            res.at<float>(i, j) = dist;
            dmax = max(dmax, dist);
        }
    }
    cout << "dmax " << dmax << endl;
    /*for(int i = 0; i < centroids.size(); i++){
        for(int j = 0; j < centroids.size(); j++){
            res.at<float>(i, j) = 1 - res.at<float>(i, j) / dmax;
            cout << "d(" << i << "," << j << "): " << res.at<float>(i, j) << endl;
        }
    }*/
    //scaleAdd(res, -1/dmax, 1, res);
    res = 1 - res / dmax;
    /*for(int i = 0; i < centroids.size(); i++){
        for(int j = 0; j < centroids.size(); j++){
            cout << "d(" << i << "," << j << "): " << res.at<float>(i, j) << endl;
        }
    }*/

    return res;
}

Vec3f CrosstalkCalculator::calc_repr(Vec3i bin, Vec3i nbins, Vec3f range){
    return Vec3f(bin[0]*range[0]/nbins[0], bin[1]*range[1]/nbins[1], bin[2]*range[2]/nbins[2]);
}

