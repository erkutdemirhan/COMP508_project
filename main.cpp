// Authors:
// 	Deniz Demircioğlu
// 	Erkut Demirhan
//
// This file includes implementation of the main routine of the program

#include <cv.h> 
#include <highgui.h> 
#include <iostream>

using namespace cv;
using namespace std;

#include "main.h"
#include "enh.h"
#include "harris.h"

int main(int argc, char** argv) {
		  Mat input_image;

		  input_image = imread(LENNA_IMAGE_PATH, CV_LOAD_IMAGE_COLOR);

		  imshow("Lenna Original", input_image);

		  Mat enhanced_image = apply_gaussian_filtering(input_image, 5.0, 5);

		  imshow("Lenna Enhanced", enhanced_image);

		  imwrite("./output_images/Lenna_enhanced.jpg", enhanced_image);

		  Mat corners_detected = detectCorners(input_image); 

		  imshow("Lenna Corners Detected", corners_detected);
		  imwrite("./output_images/Lenna_cornerdetected.jpg", corners_detected);

		  waitKey(0);
}
