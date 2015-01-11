// Authors:
// 	Deniz Demircioğlu
// 	Erkut Demirhan
//
// This file includes implementation of the main routine of the program

#include <cv.h> 
#include <highgui.h> 
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

#include "helperMethods.hpp"
#include "enh.hpp"
#include "harris.hpp"
#include "preprocessor.hpp"
#include "matching.hpp"



int main(int argc, char** argv) {
	ofstream ofile("log.txt");

	Mat input_image;
//	string image_path(argv[1]);
//
//	// get input image path from the command line
//	if(argc != 2) {
//		 cerr << "Usage: <executable_name> <input_image_path>" << endl;
//		 exit(1);
//	} else {
//		 input_image = imread(image_path, CV_LOAD_IMAGE_COLOR);
//	}
//
//	if(input_image.empty()) {
//		 cerr << "The given path below does not belong an image file!" << endl;
//		 cerr << image_path << endl;
//		 exit(1);
//	}

	string image_path;
	cin >> image_path;
	input_image = imread(image_path, CV_LOAD_IMAGE_COLOR);

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

	vector<Point> corners; 
   //	detectCorners(enhanced_image, corners);
	detectCorners2(enhanced_image, corners);

	std::cout << "number of corners: " << corners.size() << std::endl;
//	imshow(image_name+" Corners Detected", corners_detected);
	// Drawing a circle around corners
for(vector<Point>::iterator it = modelCorners.begin(); it != modelCorners.end(); it++) {
//		circle(corners_detected, *it, 5, Scalar(0), 2, 8, 0);
		line(corners_detected, Point(it->x - 5, it->y), Point(it->x + 5, it->y), Scalar(255, 0, 0), 1, 8, 0);
		line(corners_detected, Point(it->x, it->y - 5), Point(it->x, it->y + 5), Scalar(255, 0, 0), 1, 8, 0);
//		imshow(image_name+" Corners Detected", corners_detected);
//		cout << "press key: " << it->x << " " << it->y << endl;
//		waitKey(0);
	}

	Multimap2D modelMap;
	preprocess(modelCorners, modelMap);

	vector<Point> sceneCorners;
	detectCorners(enhanced_image, sceneCorners);
//	purifyCorners(sceneCorners, PURIFICATION_DISTANCE);

	std::vector<std::vector<std::pair<unsigned int, unsigned int> > > candidateMatches;

	matching(sceneCorners, modelMap, candidateMatches);

//	for (std::vector<std::vector<std::pair<unsigned int, unsigned int> > >::iterator it =
//			candidateMatches.begin(); it != candidateMatches.end(); it++) {
//		ofile << "Solution no: " << it - candidateMatches.begin() <<  "	Size: " << it->size() << endl;
//		for (std::vector<std::pair<unsigned int, unsigned int> >::iterator itLocal = it->begin(); itLocal != it->end(); itLocal++) {
//			ofile << itLocal->first << " - " << itLocal->second << "	";
//		}
//		ofile << endl;
//	}
//
//	ofile.close();

	cv::Scalar color = cv::Scalar(0, 255, 0);
	corners_detected = drawBoundary(corners_detected, modelCorners, color);

	imshow(image_name+" Corners Detected", corners_detected);
	imwrite("./output_images/"+image_name+"_cornerdetected.jpg", corners_detected);

	waitKey(0);
}
