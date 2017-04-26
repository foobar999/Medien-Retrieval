#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &vec) {
    os << "[";
    for(int i = 0; i < vec.size(); i++) {
        os << vec[i] << (i == vec.size()-1 ? "" : ", ");
    }
    os << "]";
    return os;
}

double d_cyl(cv::Vec3f col1, cv::Vec3f col2);


#endif // UTILS_H
