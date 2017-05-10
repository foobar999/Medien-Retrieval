#include "../include/TamuraDistance.h"

using namespace cv;
using namespace std;

double TamuraDistance::calc(const ImageData &dat1, const ImageData &dat2) {

	vector<Mat> A_k_list;
	vector<Mat> E_k_list;

	Mat gray_img;
	cvtColor(dat1.rgb_img, gray_img, CV_BGR2GRAY);

	Mat S_best_k(dat1.rgb_img.size(), CV_32S);
	Mat S_best_maxval(dat1.rgb_img.size(), CV_64F, Scalar(0));

	for (int k = kmin; k <= kmax; k++) {
        cout << "k " << k << endl;
		Mat A_k(dat1.rgb_img.size(), CV_64F);
		int k_pow = pow(2, k - 1);
		for (int x = 0; x < dat1.rgb_img.rows; x++) {
			for (int y = 0; y < dat1.rgb_img.cols; y++) {

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
		A_k_list.push_back(A_k);

		Mat E_k_h(dat1.rgb_img.size(), CV_64F), E_k_v(dat1.rgb_img.size(), CV_64F);
		for (int x = 0; x < dat1.rgb_img.rows; x++) {
			for (int y = 0; y < dat1.rgb_img.cols; y++) {

				E_k_h.at<double>(x, y) = fabs(A_k.at<double>(borderInterpolate(x + k_pow, A_k.rows, BORDER_REFLECT_101), borderInterpolate(y, A_k.cols, BORDER_REFLECT_101)) - A_k.at<double>(borderInterpolate(x - k_pow, A_k.rows, BORDER_REFLECT_101), borderInterpolate(y, A_k.cols, BORDER_REFLECT_101)));
				E_k_v.at<double>(x, y) = fabs(A_k.at<double>(borderInterpolate(x, A_k.rows, BORDER_REFLECT_101), borderInterpolate(y + k_pow, A_k.cols, BORDER_REFLECT_101)) - A_k.at<double>(borderInterpolate(x, A_k.rows, BORDER_REFLECT_101), borderInterpolate(y - k_pow, A_k.cols, BORDER_REFLECT_101)));

				double maxval = max(E_k_h.at<double>(x, y), E_k_v.at<double>(x, y));
				if (maxval > S_best_maxval.at<double>(x, y)) {
					S_best_maxval.at<double>(x, y) = maxval;
					S_best_k.at<int>(x, y) = pow(2, k);
				}
			}
		}
		E_k_list.push_back(E_k_h);
		E_k_list.push_back(E_k_v);
	}

	//Mat F_crs;
	//normalize(S_best_k, F_crs, )

	//cout << "S_best_k" << S_best_k << endl;
    //double F_crs = cv::sum(S_best_k)[0] / S_best_k.total();
    double F_crs = mean(S_best_k)[0];
    cout << F_crs << endl;

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


	return F_crs;
}

string TamuraDistance::get_class_name() {
	return "Tamura-Granularity-Distance";
}
