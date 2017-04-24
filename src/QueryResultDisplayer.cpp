#include "QueryResultDisplayer.h"

using namespace cv;
using namespace std;

void QueryResultDisplayer::display(Mat query_img, const vector<vector<Mat>> &results, string winname, Size thumb_size) {
    /*
    Mat query_thumb;
    cv::resize(query_img, query_thumb, thumb_size);
    vector<Mat> results_thumbs(results.size());
    for(int i = 0; i < results_thumbs.size(); i++) {
        cv::resize(results[i], results_thumbs[i], thumb_size);
    }
    // construct displayed img with 2 rows:
    // upper row: thumbnail of query img + padding
    // lower row: thumbnails of most similar images, sorted
    Mat lower_thumb_row, upper_thumb_row;
    hconcat(results_thumbs, lower_thumb_row);
    Mat query_thumb_padding(thumb_size.height, thumb_size.width*(results.size()-1), CV_8UC3, Scalar::all(0));
    hconcat(query_thumb, query_thumb_padding, upper_thumb_row);
    Mat displayed_img;
    vconcat(upper_thumb_row, lower_thumb_row, displayed_img);
    */

    Mat query_thumb;
    cv::resize(query_img, query_thumb, thumb_size);
    Mat query_thumb_padding(thumb_size.height, thumb_size.width*(results[0].size()-1), CV_8UC3, Scalar::all(0));
    Mat current_res;
    hconcat(query_thumb, query_thumb_padding, current_res);
    for(const vector<Mat> &result : results){
        vector<Mat> result_thumbs(result.size());
        for(int i = 0; i < result_thumbs.size(); i++) {
            resize(result[i], result_thumbs[i], thumb_size);
        }
        Mat next_thumb_row;
        hconcat(result_thumbs, next_thumb_row);
        vconcat(current_res, next_thumb_row, current_res);
    }

    imshow(winname, current_res);
    waitKey();
    //cvDestroyWindow(winname.c_str());
}
