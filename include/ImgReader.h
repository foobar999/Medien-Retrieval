#ifndef IMGREADER_H
#define IMGREADER_H

#include <vector>
#include <opencv2/highgui.hpp>

class ImgReader {
public:
    std::vector<std::pair<cv::Mat,std::string>> read_from_dir(std::string dirname);
};

#endif // IMGREADER_H
