// Author:
// 	Erkut Demirhan
//
// This file includes implementation of corner detection functions 

#include "harris.hpp"

//// This function takes a grayscale image as input, and returns it in grayscale format
//// with circles that show detected corners
//cv::Mat detectCorners(const cv::Mat image_gs) {

//	cv::Mat dst, dst_norm, dst_norm_scaled;

//	// Detecting corners
//	cornerHarris(image_gs, dst, BLOCK_SIZE, APERTURE_SIZE, K, cv::BORDER_DEFAULT);

//	// Normalizing
//	normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
//	convertScaleAbs(dst_norm, dst_norm_scaled);

//	// Drawing a circle around corners
//	for(int j=0; j< dst_norm.rows; j++) {
//		for(int i=0; i<dst_norm.cols; i++) {
//			if( (int) dst_norm.at<float>(j,i) > THRESHOLD) {								  
//				cv::circle(dst_norm_scaled, cv::Point(i,j), 5, cv::Scalar(0), 2, 8, 0);
//			}
//		}
//	}

//	return dst_norm_scaled;
//}



// This function takes a grayscale image as input, and calculates the coordinates of the corners in the image in the form of a vector
void detectCorners(const cv::Mat image_gs, std::vector<cv::Point>& corners) {

    cv::Mat dst, dst_norm, dst_norm_scaled;

  	// Detecting corners
  	cornerHarris(image_gs, dst, BLOCK_SIZE, APERTURE_SIZE, 
			  		 HARRIS_FREE_PARAMETER, cv::BORDER_DEFAULT);

    // Normalizing
    normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());

    // Adding the coordinates of corners into the vector
    for(int j=0; j< dst_norm.rows; j++) {
        for(int i=0; i<dst_norm.cols; i++) {
            if( (int) dst_norm.at<float>(j,i) > THRESHOLD) {
                corners.push_back(cv::Point(i,j));
            }
        }
    }
}

void detectCorners2(const cv::Mat image_gs, std::vector<cv::Point>& corners) {

		  // Parameters 
		  int maxCorners = 100; // Maximum number of corners to return
		  double qualityLevel = 0.1; // Minimal accepted quality of image corners
		  double minDistance = 5.0; // Minimum possible Euclidean distance between the returned corners
		  int blockSize = 3; // Size of an average block for computing a derivative covariation matrix
		  							// for each pixel neighborhood
		  bool useHarrisDetector = false;
		  double k = 0.04; // Free parameter to be used in Harris Detector

		  cv::goodFeaturesToTrack(image_gs, corners, maxCorners, qualityLevel, 
										  minDistance, image_gs, blockSize, useHarrisDetector, k);
}

