#include "../include/TamuraDistance.h"

using namespace cv;
using namespace std;

double TamuraDistance::calc(const ImageData &dat1, const ImageData &dat2) {

	Mat S_best1 = calc_granularity_sbest(dat1.rgb_img);
	Mat S_best2 = calc_granularity_sbest(dat2.rgb_img);

	cout << "S_best histograms:" << endl;
	Vec2f hist_range(pow(2, kmin), pow(2, kmax) + 1);
	int nbins = hist_range[1] - hist_range[0];
	cout << nbins << " bins, range " << hist_range << " (start inclusive, end exclusive)" << endl;
	Mat hist1 = HistogramCalculator().calc_1d_hist(S_best1, nbins, hist_range);
	Mat hist2 = HistogramCalculator().calc_1d_hist(S_best2, nbins, hist_range);
	cout << hist1 << endl << hist2 << endl;
	//cout << "total " << sum(hist1)[0] << "," << sum(hist2)[0] << " expected " << dat2.rgb_img.total() << endl;

	double F_crs1 = mean(S_best1)[0];
	double F_crs2 = mean(S_best2)[0];
	cout << "F_crs: " << Vec2d(F_crs1, F_crs2) << endl;
	return fabs(F_crs1 - F_crs2);
}

string TamuraDistance::get_class_name() {
	return "Tamura-Granularity-Distance";
}

Mat TamuraDistance::calc_granularity_sbest(Mat bgr_img) {
	Mat gray_img;
	cvtColor(bgr_img, gray_img, CV_BGR2GRAY);

	Mat S_best_k(bgr_img.size(), CV_32F, Scalar(0));
	Mat S_best_maxval(bgr_img.size(), CV_64F, Scalar(0));

	for (int k = kmin; k <= kmax; k++) {
		if (k == 0) {
			cout << "k=0: skipping mean calculation" << endl;
		}
		else {
			Mat A_k;
			int k_pow = pow(2, k - 1);
			Size filter_size(2 * k_pow, 2 * k_pow);
			boxFilter(gray_img, A_k, CV_64F, filter_size, Point(-1, -1), true, BORDER_REFLECT_101);

			Mat E_k_h;
			cv::absdiff(translate_img(A_k, k_pow, 0), translate_img(A_k, -k_pow, 0), E_k_h);
			Mat E_k_v;
			cv::absdiff(translate_img(A_k, 0, k_pow), translate_img(A_k, 0, -k_pow), E_k_v);

			MatExpr maxi_mask = (E_k_h > S_best_maxval) | (E_k_v > S_best_maxval);
			S_best_k.setTo(pow(2, k), maxi_mask);
			S_best_maxval = cv::max(S_best_maxval, cv::max(E_k_h, E_k_v));
		}
	}

	return S_best_k;
}


Mat TamuraDistance::translate_img(Mat img, int x, int y) {
	Mat trans_mat = (Mat_<double>(2, 3) << 1, 0, x, 0, 1, y);
	Mat res;
	warpAffine(img, res, trans_mat, img.size(), INTER_LINEAR, BORDER_REFLECT_101);
	return res;
}