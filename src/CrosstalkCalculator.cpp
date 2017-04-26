#include "../include/CrosstalkCalculator.h"

using namespace cv;
using namespace std;

Mat CrosstalkCalculator::calc(Vec3i nbins, Vec3f range){
    vector<Vec3f> sums;
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
                sums.push_back(sum);
                cout << "bin: " << bin << " color: " << calc_repr(bin, nbins, range) << " sum " << sum << endl;
    }}}
    Mat res(sums.size(), sums.size(), CV_32F);
    for(int i = 0; i < sums.size(); i++){
        for(int j = 0; j < sums.size(); j++){
            res.at<float>(i, j) = cv::norm(sums[i], sums[j]);

            }
    }
    cout << res.size() << endl;
    return res;
}

Vec3f CrosstalkCalculator::calc_repr(Vec3i bin, Vec3i nbins, Vec3f range){
    return Vec3f(bin[0]*range[0]/nbins[0], bin[1]*range[1]/nbins[1], bin[2]*range[2]/nbins[2]);
}

