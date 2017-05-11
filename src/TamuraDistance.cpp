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
    /*
    imshow("a", gray_img);
    imshow("b", translate_img(gray_img, 100, 50));
    waitKey(0);
    exit(1);
    */
    Mat S_best_k(bgr_img.size(), CV_32F);
    Mat S_best_maxval(bgr_img.size(), CV_64F, Scalar(0));

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
            MatExpr maxi_mask = (E_k_h > S_best_maxval) | (E_k_v > S_best_maxval);
            S_best_k.setTo(pow(2, k), maxi_mask);
            S_best_maxval = cv::max(S_best_maxval, cv::max(E_k_h, E_k_v));
        }
        //E_k_list.push_back(E_k_h);
        //E_k_list.push_back(E_k_v);
    }

    //Mat F_crs;
    //normalize(S_best_k, F_crs, )

    /*
    //Mat res;
    //boxFilter(A_k_list[3], res, -1, Size(8, 8));
    //cout << (res == A_k_list[3]) << endl;


    Mat dst;
    normalize(A_k_list.at(3), dst, 0, 1, cv::NORM_MINMAX);
    imshow("test", dst);
    waitKey(0);

    //imshow("abc", A_k_list.front());
    //waitKey(0);
    return 8;
    //*/

    //double minv, maxv;
    //minMaxLoc(S_best_k, &minv, &maxv);
    //cout << "values min " << minv << " max " << maxv << endl;
    //cout << "corners: " << Vec4f(S_best_k.at<float>(0,0),hist.at<float>(S_best_k.rows-1,0),hist.at<float>(0,S_best_k.cols-1),hist.at<float>(S_best_k.rows-1,S_best_k.cols-1)) << endl;
    //vector<Point> locations;
    //findNonZero(S_best_k == 0, locations);
    //cout << "zero locations " << locations << endl;

    //cout << "S_best_k" << S_best_k << endl;
    //double F_crs = cv::sum(S_best_k)[0] / S_best_k.total();
    //return mean(S_best_k)[0];
    return S_best_k;
}


Mat TamuraDistance::translate_img(Mat img, int x, int y) {
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, x, 0, 1, y);
    Mat res;
    warpAffine(img,res,trans_mat,img.size(), INTER_LINEAR, BORDER_REFLECT_101);
    return res;
}
