// Author:
// 	Erkut Demirhan
//
// Includes functions and parameters to detect corners using Harris detector

#ifndef HARRIS_HPP
#define HARRIS_HPP

#include <cv.h>
#include <vector>

// Detector parameters
#define BLOCK_SIZE 2 // Neighborhood size
#define APERTURE_SIZE 3 // Apperture parameter for the Sobel() operator
								// (i.e., size of the Sobel kernel)
#define HARRIS_FREE_PARAMETER 0.04 // the parameter that is used to
											  // calculate the Harris Operator 

// Threshold for the Harris Operator
#define THRESHOLD 125

// Detects and shows corners in given grayscale input image
//cv::Mat detectCorners(const cv::Mat image_gs);
void detectCorners(const cv::Mat image_gs, std::vector<cv::Point>& corners);

void detectCorners2(const cv::Mat image_gs, std::vector<cv::Point>& corners);

// Using draws convex hull of given coordinate points into given input image 
// with given color value, and returns the resulting it
cv::Mat drawBoundary(const cv::Mat input_image, 
					 		const std::vector<cv::Point> points,
							const cv::Scalar color);

#endif
