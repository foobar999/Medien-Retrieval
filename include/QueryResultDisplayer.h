#ifndef QUERYRESULTDISPLAYER_H
#define QUERYRESULTDISPLAYER_H

#include <vector>
#include <opencv2/opencv.hpp>

class QueryResultDisplayer {
public:
    void display(cv::Mat query_img, const std::vector<std::vector<cv::Mat>> &results, std::string winname,
                 cv::Size thumb_size = cv::Size(100,100));

};

#endif // QUERYRESULTDISPLAYER_H
