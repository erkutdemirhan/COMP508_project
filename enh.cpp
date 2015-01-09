// Erkut Demirhan
//
// Implementation of functions to be used for enhancing input images for 
// corner detection

#include "enh.hpp"

cv::Mat apply_gaussian_filtering(const cv::Mat image, const float std_dev, const int filter_size) {
	cv::Mat input_yCrCb, result_yCrCb, result_rgb;
	std::vector<cv::Mat> yCrCb_channels;

	// convert RGB image into YCrCb format
	cv::cvtColor(image, input_yCrCb, CV_BGR2YCrCb);

	// split the YCrCb image into its channels
	cv::split(input_yCrCb, yCrCb_channels);

	// apply Gaussian filtering on the Y channel
	cv::GaussianBlur(yCrCb_channels[0], yCrCb_channels[0], cv::Size(filter_size, filter_size), std_dev);

	// merge resulting YCrCb channels into an image
	cv::merge(yCrCb_channels, result_yCrCb);

	// convert resulting YCrCb image into RGB format
	cv::cvtColor(result_yCrCb, result_rgb, CV_YCrCb2BGR);

	return result_rgb;
}

cv::Mat apply_histeq(const cv::Mat rgb_image) {
	// convert input image into grayscale
	cv::Mat input_graysc;
	cv::cvtColor(rgb_image, input_graysc, CV_BGR2GRAY);

	// apply histogram equalization
	cv::Mat output_graysc;
	cv::equalizeHist(input_graysc, output_graysc);

	return output_graysc;
}

		 
		  




