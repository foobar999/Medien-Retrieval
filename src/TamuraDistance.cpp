#include "../include/TamuraDistance.h"

using namespace cv;
using namespace std;

double TamuraDistance::calc(const ImageData &dat1, const ImageData &dat2) {

    double F_crs1 = calc_granularity(dat1.rgb_img);
    double F_crs2 = calc_granularity(dat2.rgb_img);
    cout << "F_crs: " << Vec2d(F_crs1, F_crs2) << endl;

    // TODO normalisierung
    // TODO vermeide mehrfachberechnung f�r 1
    // TODO performance?
    return fabs(F_crs1 - F_crs2);
}

string TamuraDistance::get_class_name() {
	return "Tamura-Granularity-Distance";
}


double TamuraDistance::calc_granularity(Mat bgr_img){
    //vector<Mat> A_k_list;
	//vector<Mat> E_k_list;

	Mat gray_img;
	cvtColor(bgr_img, gray_img, CV_BGR2GRAY);

	Mat S_best_k(bgr_img.size(), CV_32S);
	Mat S_best_maxval(bgr_img.size(), CV_64F, Scalar(0));

	for (int k = kmin; k <= kmax; k++) {
        cout << "k " << k << endl;
		Mat A_k(bgr_img.size(), CV_64F);
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

        boxFilter(gray_img, A_k, CV_64F, Size(2*k_pow,2*k_pow), Point(-1,-1), true, BORDER_REFLECT_101);
        //A_k /= pow(2, 2 * k);
		//A_k_list.push_back(A_k);

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

	//cout << "S_best_k" << S_best_k << endl;
    //double F_crs = cv::sum(S_best_k)[0] / S_best_k.total();
    return mean(S_best_k)[0];

}
