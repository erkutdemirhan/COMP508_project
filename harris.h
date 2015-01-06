// Author:
// 	Erkut Demirhan
//
// Includes functions and parameters to detect corners using Harris detector

#ifndef HARRIS_H
#define HARRIS_H

// Detector parameters
#define BLOCK_SIZE 2
#define APERTURE_SIZE 3
#define K 0.04

// Threshold for the Harris Operator
#define THRESHOLD 200

Mat detectCorners(Mat rgb_image);

#endif
