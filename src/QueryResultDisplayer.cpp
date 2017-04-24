#include "QueryResultDisplayer.h"

using namespace cv;
using namespace std;

void QueryResultDisplayer::display(Mat query_img, const vector<vector<Mat>> &results, string winname, Size thumb_size) {
    assert(results.size() > 0);
    Mat current_res = create_query_img_thumb_row(query_img, thumb_size, results[0].size()-1);
    for(const vector<Mat> &result : results) {
        Mat next_row = create_query_result_thumb_row(result, thumb_size);
        vconcat(current_res, next_row, current_res);
    }
    imshow(winname, current_res);
    waitKey();
    //cvDestroyWindow(winname.c_str());
}

Mat QueryResultDisplayer::create_query_img_thumb_row(Mat query_img, Size thumb_size, int num_padding_thumbs) {
    Mat query_thumb;
    resize(query_img, query_thumb, thumb_size);
    Mat query_thumb_padding(thumb_size.height, thumb_size.width * num_padding_thumbs, CV_8UC3, Scalar::all(0));
    Mat query_thumb_row;
    hconcat(query_thumb, query_thumb_padding, query_thumb_row);
    return query_thumb_row;
}

Mat QueryResultDisplayer::create_query_result_thumb_row(const vector<Mat> &result, Size thumb_size) {
    vector<Mat> result_thumbs(result.size());
    for(int i = 0; i < result_thumbs.size(); i++) {
        resize(result[i], result_thumbs[i], thumb_size);
    }
    Mat query_res_thumb_row;
    hconcat(result_thumbs, query_res_thumb_row);
    return query_res_thumb_row;
}




