// Authors:
// 	Deniz Demircioğlu
// 	Erkut Demirhan
//
// This file includes implementation of the main routine of the program

#include <cv.h> 
#include <highgui.h> 
#include <iostream>
#include "main.h"
#include "enh.h"

int main(int argc, char** argv) {
		  cv::Mat input_image;

		  input_image = cv::imread(LENNA_IMAGE_PATH, CV_LOAD_IMAGE_COLOR);

		  cv::imshow("Lenna Original", input_image);

		  cv::Mat enhanced_image = apply_gaussian_filtering(input_image,
																			 5.0, 5);

		  cv::imshow("Lenna Enhanced", enhanced_image);

		  cv::imwrite("./output_images/Lenna_output.jpg", enhanced_image);
		  cv::waitKey(0);
}
