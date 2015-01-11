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

	Mat input_image, scene_image;

	string input_image_path, scene_image_path;
	cout << "Input image: ";
	cin >> input_image_path;
	input_image = imread(input_image_path, CV_LOAD_IMAGE_COLOR);

	cout << "Scene image: ";
	cin >> scene_image_path;
	scene_image = imread(scene_image_path, CV_LOAD_IMAGE_COLOR);

	///////////////////////////////////////////////////////////////////////////////////////////
	// get input image name
	string input_image_name = input_image_path;
	unsigned last_slash_index = input_image_name.find_last_of("/");

	if(last_slash_index > 0 && last_slash_index < input_image_name.length()) {
		input_image_name = input_image_name.substr(last_slash_index+1);
	}

	unsigned dot_index = input_image_name.find_last_of(".");

	if(dot_index > 0 && dot_index < input_image_name.length()) {
		input_image_name = input_image_name.substr(0, dot_index);
	}

	imshow(input_image_name+" Original Input", input_image);

	Mat enhanced_input_image = apply_histeq(input_image);

	imshow(input_image_name+" Enhanced Input", enhanced_input_image);

	imwrite("./output_images/"+input_image_name+"_enhanced(input).jpg", enhanced_input_image);

	///////////////////////////////////////////////////////////////////////////////////////////
	// get scene image name
	string scene_image_name = scene_image_path;
	last_slash_index = scene_image_name.find_last_of("/");

	if(last_slash_index > 0 && last_slash_index < scene_image_name.length()) {
		scene_image_name = scene_image_name.substr(last_slash_index+1);
	}

	dot_index = scene_image_name.find_last_of(".");

	if(dot_index > 0 && dot_index < scene_image_name.length()) {
		scene_image_name = scene_image_name.substr(0, dot_index);
	}

	imshow(scene_image_name+" Original Scene", scene_image);

	Mat enhanced_scene_image = apply_histeq(scene_image);

	imshow(scene_image_name+" Enhanced Scene", enhanced_scene_image);

	imwrite("./output_images/"+scene_image_name+"_enhanced(scene).jpg", enhanced_scene_image);

	///////////////////////////////////////////////////////////////////////////////////////////


	vector<Point> modelCorners;
   //	detectCorners(enhanced_image, corners);
	detectCorners2(enhanced_input_image, modelCorners);

	Multimap2D modelMap;
	preprocess(modelCorners, modelMap);

	vector<Point> sceneCorners;
//	detectCorners(enhanced_scene_image, sceneCorners);
	detectCorners2(enhanced_scene_image, sceneCorners);

	std::vector<std::vector<std::pair<unsigned int, unsigned int> > > candidateMatches;

	matching(sceneCorners, modelMap, candidateMatches);

	Mat corners_detected = input_image.clone();
	std::cout << "Number of input corners: " << modelCorners.size()	<< std::endl;
//	imshow(input_image_name+" Corners Detected", corners_detected);
	// Drawing a crosshair around corners
	for (vector<Point>::iterator it = modelCorners.begin();	it != modelCorners.end(); it++) {
//		circle(corners_detected, *it, 5, Scalar(0), 2, 8, 0);
		line(corners_detected, Point(it->x - 5, it->y), Point(it->x + 5, it->y), Scalar(255, 0, 0), 1, 8, 0);
		line(corners_detected, Point(it->x, it->y - 5), Point(it->x, it->y + 5), Scalar(255, 0, 0), 1, 8, 0);
//		imshow(input_image_name+" Corners Detected", corners_detected);
//		cout << "press key: " << it->x << " " << it->y << endl;
//		waitKey(0);
	}

	cv::Scalar color = cv::Scalar(0, 255, 0);
	corners_detected = drawBoundary(corners_detected, modelCorners, color);

	imshow(input_image_name+" Corners Detected Input", corners_detected);
	imwrite("./output_images/"+input_image_name+"_cornerdetected.jpg", corners_detected);


	corners_detected = scene_image.clone();
	std::cout << "Number of scene corners: " << sceneCorners.size()	<< std::endl;
//	imshow(scene_image_name+" Corners Detected", corners_detected);
	// Drawing a crosshair around corners
	for (vector<Point>::iterator it = sceneCorners.begin();	it != sceneCorners.end(); it++) {
//		circle(corners_detected, *it, 5, Scalar(0), 2, 8, 0);
		line(corners_detected, Point(it->x - 5, it->y), Point(it->x + 5, it->y), Scalar(255, 0, 0), 1, 8, 0);
		line(corners_detected, Point(it->x, it->y - 5), Point(it->x, it->y + 5), Scalar(255, 0, 0), 1, 8, 0);
//		imshow(scene_image_name+" Corners Detected", corners_detected);
//		cout << "press key: " << it->x << " " << it->y << endl;
//		waitKey(0);
	}

	imshow(scene_image_name+" Corners Detected Scene", corners_detected);
	imwrite("./output_images/"+scene_image_name+"_cornerdetected.jpg", corners_detected);

	/////////////////////////////////////////////////////////////////////////////////////////
// Outputs the matching corner pairs into log.txt
	for (std::vector<std::vector<std::pair<unsigned int, unsigned int> > >::iterator it =
			candidateMatches.begin(); it != candidateMatches.end(); it++) {
		ofile << "Solution no: " << it - candidateMatches.begin() <<  "	Size: " << it->size() << endl;
		for (std::vector<std::pair<unsigned int, unsigned int> >::iterator itLocal = it->begin(); itLocal != it->end(); itLocal++) {
			ofile << itLocal->first << " - " << itLocal->second << "	";
		}
		ofile << endl;
	}

	ofile.close();

//	if (candidateMatches.empty()) {
//		cout << "NO MATCHING OBJECT FOUND!" << endl;
//		return 0;
//	}

	int max_size, max_index;
	max_size = -1;
	max_index = -1;
	for (unsigned int it = 0; it < candidateMatches.size(); it++) {
		if((int) candidateMatches.at(it).size() > max_size) {
			max_size = (int) candidateMatches.at(it).size();
			max_index = (int) it;
		}
	}

	std::vector<cv::Point> matchingCorners;
	if (max_index == -1) {
		cout << "NO MATCHING OBJECT FOUND!" << endl;
//		return 0;
	}
	else {
		for (std::vector<std::pair<unsigned int, unsigned int> >::iterator itLocal = candidateMatches.at(max_index).begin(); itLocal != candidateMatches.at(max_index).end(); itLocal++) {
			matchingCorners.push_back(sceneCorners.at(itLocal->second));
		}
	}

	corners_detected = scene_image.clone();
	std::cout << "Number of matching scene corners: " << matchingCorners.size()	<< std::endl;
//	imshow(scene_image_name+" Corners Detected", corners_detected);
	// Drawing a crosshair around corners
	for (vector<Point>::iterator it = matchingCorners.begin();	it != matchingCorners.end(); it++) {
//		circle(corners_detected, *it, 5, Scalar(0), 2, 8, 0);
		line(corners_detected, Point(it->x - 5, it->y), Point(it->x + 5, it->y), Scalar(255, 0, 0), 1, 8, 0);
		line(corners_detected, Point(it->x, it->y - 5), Point(it->x, it->y + 5), Scalar(255, 0, 0), 1, 8, 0);
//		imshow(scene_image_name+" Corners Detected", corners_detected);
//		cout << "press key: " << it->x << " " << it->y << endl;
//		waitKey(0);
	}

	color = cv::Scalar(0, 0, 255);
	corners_detected = drawBoundary(corners_detected, matchingCorners, color);

	imshow(scene_image_name+" Object Detected", corners_detected);
	imwrite("./output_images/"+scene_image_name+"_objectdetected.jpg", corners_detected);


	waitKey(0);
}
