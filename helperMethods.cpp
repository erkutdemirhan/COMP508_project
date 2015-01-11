/*
 * helperMethods.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#include "helperMethods.hpp"


void purifyCorners(std::vector<cv::Point>& original, double distance) {
	std::vector<cv::Point> result;

	int* check  = 0;
	check = new int[original.size()];
	for (unsigned int i = 0; i < original.size(); i++) {
		check[i] = 0;
	}

	int current = 0;
	for (unsigned int i = 0; i < original.size() - 1; i++) {
		current = 0;
		for (unsigned int j = i+1; j < original.size(); j++) {
			if (check[j] > 0) {
				continue;
			}
			int distX = (original.at(i).x - original.at(j).x);
			int distY = (original.at(i).y - original.at(j).y);
			if ((distX * distX + distY * distY) < distance * distance) {
				current++;
				check[j] = current;
			}
		}
		check[i] = current;
	}

	for (unsigned int i = 0; i < original.size(); i++) {
		if (check[i] == 0) {
			result.push_back(original.at(i));
		}
	}

	original = result;
}


// The corner comparison operator for sorting in ascending order
bool cornerSorterAscending(cv::Point pi, cv::Point pj) {
	if (pi.y < pj.y) {
		return true;
	}
	else if (pi.y > pj.y) {
		return false;
	}
	else if (pi.x <= pj.x) {
		return true;
	}
	else {
		return false;
	}
}


// Using draws convex hull of given coordinate points into given input image
// with given color value, and returns the resulting it
cv::Mat drawBoundary(const cv::Mat input_image,
					 		const std::vector<cv::Point> points,
							const cv::Scalar color) {
		  // Finds the convex hull object from given input points
		  std::vector<std::vector<cv::Point> > hull(1);
		  cv::convexHull(points, hull[0], false, false);

		  // Draws the convex hull into a copy of the input image, with given
		  // color values
		  cv::Mat result_image = input_image.clone();
		  cv::drawContours(result_image, hull, 0, color, 2, 8);

		  return result_image;
}


// Granulates the given vector coordinates according to the granularity parameter
//	Vector result: the result vector holding the granulated coordinates
//	Vector v: the vector to be granulated
//	double GranulationRate: the parameters which determines the granularity of the coordinates in the model map
void granulate(Eigen::Vector2i& result, const Eigen::Vector2d& v, const double granulationRate) {
	result(0) = (int) round((double) v(0) / granulationRate);
	result(1) = (int) round((double) v(1) / granulationRate);
//	std::cout << result.transpose();
//	std::cout << std::endl;
}

// Finds the euclidian distance between two 2d vectors
double euclidianDistance(const Eigen::Vector2d& a, const Eigen::Vector2d& b) {
	return (a - b).norm();
}

// Finds the new coordinates of a position vector according to a new basis defined by 2 basis vector and the displacement (for the origin)
//	Vector e1: The x axis of the new basis
//	Vector e2: The y axis of the new basis
//	double scalingFactor: The scaling factor for the new coordinates
//	Vector displacement: The translation amount required for the new basis origin
//	Vector coordinates: The coordinates that are going to be evaluated in the new basis
//	Vector result: The result vector holding the transformed coordinates
void findTransformedCoordinates(const Eigen::Vector2d& e1, const Eigen::Vector2d& e2, double scalingFactor,
		const Eigen::Vector2d& displacement, const Eigen::Vector2d& coordinates, Eigen::Vector2d& result) {
	Eigen::Matrix2d newBasis;
	newBasis.col(0) = e1;
	newBasis.col(1) = e2;
	result = newBasis.inverse() * ((coordinates - displacement) / scalingFactor);
}



