#ifndef QUERYRESULTDISPLAYER_H
#define QUERYRESULTDISPLAYER_H

#include <vector>
#include <opencv2/opencv.hpp>

class QueryResultDisplayer {
public:
    void display(cv::Mat query_img, const std::vector<cv::Mat> &results,
                 cv::Size thumb_size = cv::Size(200,200), std::string winname = "most similar results");

};

#endif // QUERYRESULTDISPLAYER_H
