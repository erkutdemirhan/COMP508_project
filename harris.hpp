// Author:
// 	Erkut Demirhan
//
// Includes functions and parameters to detect corners using Harris detector

#ifndef HARRIS_HPP
#define HARRIS_HPP

#include <cv.h>
#include <vector>

// Detector parameters
#define BLOCK_SIZE 2
#define APERTURE_SIZE 3
#define K 0.04

// Threshold for the Harris Operator
#define THRESHOLD 150

// Detects and shows corners in given grayscale input image
//cv::Mat detectCorners(const cv::Mat image_gs);
std::vector<cv::Point> detectCorners(const cv::Mat image_gs);

// Using draws convex hull of given coordinate points into given input image 
// with given color value, and returns the resulting it
cv::Mat drawBoundary(const cv::Mat input_image, 
					 		const std::vector<cv::Point> points,
							const cv::Scalar color);

#endif
