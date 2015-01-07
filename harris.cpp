// Author:
// 	Erkut Demirhan
//
// This file includes implementation of corner detection functions 

#include <cv.h>

using namespace cv;

#include "harris.h"

// This function takes a grayscale image as input, and returns it in grayscale format
// with circles that show detected corners
Mat detectCorners(const Mat image_gs) {

		  Mat dst, dst_norm, dst_norm_scaled;

		  // Detecting corners
		  cornerHarris(image_gs, dst, BLOCK_SIZE, APERTURE_SIZE, K, BORDER_DEFAULT);

		  // Normalizing
		  normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
		  convertScaleAbs(dst_norm, dst_norm_scaled);

		  // Drawing a circle around corners
		  for(int j=0; j< dst_norm.rows; j++) {
					 for(int i=0; i<dst_norm.cols; i++) {
								if( (int) dst_norm.at<float>(j,i) > THRESHOLD) {
										  circle(dst_norm_scaled, Point(i,j), 5, Scalar(0), 2, 8, 0);
								}
					 }
		  }

		  return dst_norm_scaled;
}
