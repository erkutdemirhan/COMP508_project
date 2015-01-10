// Authors:
// 	Deniz Demircioğlu
// 	Erkut Demirhan
//
// This file includes implementation of the main routine of the program

#include <cv.h> 
#include <highgui.h> 
#include <iostream>

//#include <Eigen/Geometry>

using namespace cv;
using namespace std;

#include "enh.hpp"
#include "harris.hpp"

//int main() {
//	Eigen::Vector2d e1(1,0);
//	Eigen::Rotation2D<double> rm(M_PI_2);
//	cout << rm*e1;
//	cout << endl;
//	Eigen::Matrix2d r;
//	r << 0, -1, 1, 0;
//	cout << r;
//	cout << endl;
//	cout << r * e1;
//	return 0;
//}

int main(int argc, char** argv) {
	Mat input_image;
	string image_path(argv[1]);

	// get input image path from the command line
	if(argc != 2) {
		 cerr << "Usage: <executable_name> <input_image_path>" << endl;
		 exit(1);
	} else {
		 input_image = imread(image_path, CV_LOAD_IMAGE_COLOR);
	}

	if(input_image.empty()) {
		 cerr << "The given path below does not belong an image file!" << endl;
		 cerr << image_path << endl;
		 exit(1);
	}

	// get input image name
	string image_name = image_path;
	unsigned last_slash_index = image_name.find_last_of("/");

	if(last_slash_index > 0 && last_slash_index < image_name.length()) {
		 image_name = image_name.substr(last_slash_index+1);
	}

	unsigned dot_index = image_name.find_last_of(".");

	if(dot_index > 0 && dot_index < image_name.length()) {
		 image_name = image_name.substr(0, dot_index);
	}

	imshow(image_name+" Original", input_image);

	Mat enhanced_image = apply_histeq(input_image);

	imshow(image_name+" Enhanced", enhanced_image);

	imwrite("./output_images/"+image_name+"_enhanced.jpg", enhanced_image);

	Mat corners_detected = input_image.clone();
	vector<Point> corners = detectCorners(enhanced_image);

	// Drawing a circle around corners
	for(vector<Point>::iterator it = corners.begin(); it != corners.end(); it++) {
		circle(corners_detected, *it, 5, Scalar(0), 2, 8, 0);
	}

	imshow(image_name+" Corners Detected", corners_detected);
	imwrite("./output_images/"+image_name+"_cornerdetected.jpg", corners_detected);

	waitKey(0);
}
