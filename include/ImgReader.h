#ifndef IMGREADER_H
#define IMGREADER_H

#include <vector>
#include <opencv2/highgui.hpp>

class ImgReader {
public:
    std::vector<std::string> get_filenames_from_dir(std::string dirname);
    std::vector<cv::Mat> read_imgs_from_filenames(const std::vector<std::string> &filenames);
};

#endif // IMGREADER_H
