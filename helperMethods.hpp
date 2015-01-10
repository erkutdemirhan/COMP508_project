/*
 * helperMethods.hpp
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#ifndef HELPERMETHODS_HPP_
#define HELPERMETHODS_HPP_

#include <Eigen/Geometry>
#include <cv.h>

bool cornerSorterAscending(cv::Point pi, cv::Point pj);
void granulate(Eigen::Vector2i& result, const Eigen::Vector2d& v, const double granulationRate);
double euclidianDistance(const Eigen::Vector2d& a, const Eigen::Vector2d& b);
void findTransformedCoordinates(const Eigen::Vector2d& e1, const Eigen::Vector2d& e2, double scalingFactor,
		const Eigen::Vector2d& displacement, const Eigen::Vector2d& coordinates, Eigen::Vector2d& result);

#endif /* HELPERMETHODS_HPP_ */
