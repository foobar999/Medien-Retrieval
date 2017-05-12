#include "../include/TamuraDistance.h"

using namespace cv;
using namespace std;

double TamuraDistance::calc(const ImageData &dat1, const ImageData &dat2) {

    Mat S_best1 = calc_granularity_sbest(dat1.rgb_img);
    Mat S_best2 = calc_granularity_sbest(dat2.rgb_img);

    cout << "S_best histograms:" << endl;
    Vec2f hist_range(pow(2,kmin), pow(2,kmax)+1);
    int nbins = hist_range[1] - hist_range[0];
    cout << nbins << " bins, range " << hist_range << " (start inclusive, end exclusive)" << endl;
    Mat hist1 = HistogramCalculator().calc_1d_hist(S_best1, nbins, hist_range);
    Mat hist2 = HistogramCalculator().calc_1d_hist(S_best2, nbins, hist_range);
    cout << hist1 << endl << hist2 << endl;
    //cout << "total " << sum(hist1)[0] << "," << sum(hist2)[0] << " expected " << dat2.rgb_img.total() << endl;

    double F_crs1 = mean(S_best1)[0], F_crs2 = mean(S_best2)[0];
    cout << "F_crs: " << Vec2d(F_crs1, F_crs2) << endl;
    return fabs(F_crs1 - F_crs2);
}

string TamuraDistance::get_class_name() {
    return "Tamura-Granularity-Distance";
}

Mat TamuraDistance::calc_granularity_sbest(Mat bgr_img) {
    //vector<Mat> A_k_list;
    //vector<Mat> E_k_list;

    Mat gray_img;
    cvtColor(bgr_img, gray_img, CV_BGR2GRAY);
    Mat S_best_k(bgr_img.size(), CV_32F);   // speichert Summe aller k, bei denen E_k maximal war
    Mat S_best_maxval(bgr_img.size(), CV_64F, Scalar(0));   // speichert akt. Maximum fü E_k
    Mat S_num_best_ks(bgr_img.size(), CV_32F, Scalar(1));   // zählt, bei wie vielen k E_k maximal war
    // E_k_h, E_k_v werden je getrennt berücksichtigt

    for (int k = kmin; k <= kmax; k++) {
        if(k == 0) {
            cout << "k=0: skipping mean calculation" << endl;
        } else {
            Mat A_k;
            int k_pow = pow(2, k - 1);
            /*
            for (int x = 0; x < bgr_img.rows; x++) {
                for (int y = 0; y < bgr_img.cols; y++) {

                    double sum = 0;
                    for (int i = x - k_pow; i < x + k_pow; i++) {
                        for (int j = y - k_pow; j < y + k_pow; j++) {
                            // Out of range pixels are obtained by mirroring at the edge	alt: BORDER_WRAP
                            sum += gray_img.at<uchar>(borderInterpolate(i, gray_img.rows, BORDER_REFLECT_101), borderInterpolate(j, gray_img.cols, BORDER_REFLECT_101));

                        }
                    }
                    A_k.at<double>(x, y) = sum / pow(2, 2 * k);

                }
            }
            */
            Size filter_size(2*k_pow, 2*k_pow);
            boxFilter(gray_img, A_k, CV_64F, filter_size, Point(-1,-1), true, BORDER_REFLECT_101);

            //cout << "A_k corners: " << Vec4f(A_k.at<float>(0,0),A_k.at<float>(A_k.rows-1,0),A_k.at<float>(0,A_k.cols-1),A_k.at<float>(A_k.rows-1,A_k.cols-1)) << endl;

            //A_k /= pow(2, 2 * k);
            //A_k_list.push_back(A_k);

            /*
            Mat E_k_h(bgr_img.size(), CV_64F), E_k_v(bgr_img.size(), CV_64F);
            for (int x = 0; x < bgr_img.rows; x++) {
                for (int y = 0; y < bgr_img.cols; y++) {

                    E_k_h.at<double>(x, y) = fabs(A_k.at<double>(borderInterpolate(x + k_pow, A_k.rows, BORDER_REFLECT_101), borderInterpolate(y, A_k.cols, BORDER_REFLECT_101)) - A_k.at<double>(borderInterpolate(x - k_pow, A_k.rows, BORDER_REFLECT_101), borderInterpolate(y, A_k.cols, BORDER_REFLECT_101)));
                    E_k_v.at<double>(x, y) = fabs(A_k.at<double>(borderInterpolate(x, A_k.rows, BORDER_REFLECT_101), borderInterpolate(y + k_pow, A_k.cols, BORDER_REFLECT_101)) - A_k.at<double>(borderInterpolate(x, A_k.rows, BORDER_REFLECT_101), borderInterpolate(y - k_pow, A_k.cols, BORDER_REFLECT_101)));

                    double maxval = max(E_k_h.at<double>(x, y), E_k_v.at<double>(x, y));
                    if (maxval > S_best_maxval.at<double>(x, y)) {
                        S_best_maxval.at<double>(x, y) = maxval;
                        S_best_k.at<int>(x, y) = pow(2, k);
                    }
                }
            }
            */
            /*
            Mat dst;
            normalize(A_k, dst, 0, 1, cv::NORM_MINMAX);
            imshow("test", dst);
            imshow("test2", translateImg(dst, 20, 30));
            waitKey(0);
            */

            Mat E_k_h;
            cv::absdiff(translate_img(A_k, k_pow, 0), translate_img(A_k, -k_pow, 0), E_k_h);
            Mat E_k_v;
            cv::absdiff(translate_img(A_k, 0, k_pow), translate_img(A_k, 0, -k_pow), E_k_v);

            /*
            for (int x = 0; x < bgr_img.rows; x++) {
                for (int y = 0; y < bgr_img.cols; y++) {
                    double maxval = max(E_k_h.at<double>(x, y), E_k_v.at<double>(x, y));
                    if (maxval > S_best_maxval.at<double>(x, y)) {
                        S_best_maxval.at<double>(x, y) = maxval;
                        S_best_k.at<int>(x, y) = pow(2, k);
                    }
                }
            }
            */

            /*
            MatExpr maxi_mask = (E_k_h > S_best_maxval) | (E_k_v > S_best_maxval);
            S_best_k.setTo(pow(2, k), maxi_mask);
            MatExpr same_mask = E_k_h == S_best_maxval;
            S_best_maxval = cv::max(S_best_maxval, cv::max(E_k_h, E_k_v));
            */

            update_sbest_matrices(E_k_h, k, S_best_k, S_best_maxval, S_num_best_ks);
            update_sbest_matrices(E_k_v, k, S_best_k, S_best_maxval, S_num_best_ks);
        }
    }

    divide(S_best_k, S_num_best_ks, S_best_k);
    // S_best_k = 2 ^ S_best_k
    exp(S_best_k * std::log(2), S_best_k);

    return S_best_k;
}


Mat TamuraDistance::translate_img(Mat img, int x, int y) {
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, x, 0, 1, y);
    Mat res;
    warpAffine(img,res,trans_mat,img.size(), INTER_LINEAR, BORDER_REFLECT_101);
    return res;
}


void TamuraDistance::update_sbest_matrices(Mat E_k, int k, Mat &S_best_k, Mat &S_best_maxval, Mat &S_num_best_ks) {
    // falls Element in E_k größer: setze zug. Zähler in
    // S_num_best_ks auf 1 zurück, speichere zug. k in S_best_k
    MatExpr greater_mask = E_k > S_best_maxval;
    S_best_k.setTo(k, greater_mask);
    S_num_best_ks.setTo(1, greater_mask);

    // falls Element in E_k gleich: erhöhe zug. Zähler in
    // S_num_best_ks um 1, addiere zug. k in S_best_k
    MatExpr equal_mask = E_k == S_best_maxval;
    add(S_best_k, k, S_best_k, equal_mask);
    add(S_num_best_ks, 1, S_num_best_ks, equal_mask);

    S_best_maxval = cv::max(S_best_maxval, E_k);
}
