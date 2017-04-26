#include "../include/utils.h"

using namespace std;

double d_cyl(cv::Vec3f col1, cv::Vec3f col2){
    double dv = abs(col1[2] - col2[2]);
    double theta = abs(col1[0] - col2[0]) <= 180 ?
        abs(col1[0] - col2[0]) : 360 - abs(col1[0] - col2[0]);
    double dc = sqrt(col1[1] * col1[1] + col2[1] * col2[1] - 2 * col1[1] * col2[1] * cos(theta));

    return sqrt(dv * dv + dc * dc);
}
