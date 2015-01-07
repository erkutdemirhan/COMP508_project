// Erkut Demirhan
//
// Implementation of functions to be used for enhancing input images for 
// corner detection

#include <cv.h> 

using namespace cv;
using namespace std;

Mat apply_gaussian_filtering(const Mat image,
					 						const float std_dev,
											const int filter_size) {
		  Mat input_yCrCb, result_yCrCb, result_rgb;
		  vector<Mat> yCrCb_channels;

		  // convert RGB image into YCrCb format
		  cvtColor(image, input_yCrCb, CV_BGR2YCrCb);

		  // split the YCrCb image into its channels
		  split(input_yCrCb, yCrCb_channels);

		  // apply Gaussian filtering on the Y channel
		  GaussianBlur(yCrCb_channels[0], yCrCb_channels[0],
					  		Size(filter_size, filter_size),
					  		std_dev);

		  // merge resulting YCrCb channels into an image
		  merge(yCrCb_channels, result_yCrCb);

		  // convert resulting YCrCb image into RGB format
		  cvtColor(result_yCrCb, result_rgb, CV_YCrCb2BGR);

		  return result_rgb;
}

Mat apply_histeq(const Mat rgb_image) {
		  // convert input image into grayscale
		  Mat input_graysc;
		  cvtColor(rgb_image, input_graysc, CV_BGR2GRAY);

		  // apply histogram equalization
		  Mat output_graysc;
		  equalizeHist(input_graysc, output_graysc);

		  return output_graysc;
}

		 
		  




