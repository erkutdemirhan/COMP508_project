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
#define KK 0.04

// Threshold for the Harris Operator
#define THRESHOLD 150

// Detects and shows corners in given grayscale input image
//cv::Mat detectCorners(const cv::Mat image_gs);
void detectCorners(const cv::Mat image_gs, std::vector<cv::Point>& corners);


#endif
