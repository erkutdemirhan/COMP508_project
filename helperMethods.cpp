/*
 * helperMethods.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#include "helperMethods.hpp"

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

// Granulates the given vector coordinates according to the granularity parameter
//	Vector result: the result vector holding the granulated coordinates
//	Vector v: the vector to be granulated
//	double GranulationRate: the parameters which determines the granularity of the coordinates in the model map
void granulate(Eigen::Vector2i& result, const Eigen::Vector2d& v, const double granulationRate) {
	result(0) = (int) round((double) v(0) / granulationRate);
	result(1) = (int) round((double) v(1) / granulationRate);
}


//void granulate(Eigen::Vector2i& result, const Eigen::Vector2d& v, const double granulationRate) {
//	result(0) = (int) round((double) v(0) / granulationRate);
//	result(1) = (int) round((double) v(1) / granulationRate);
//}

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
