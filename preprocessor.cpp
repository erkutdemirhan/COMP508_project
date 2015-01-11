
#include "preprocessor.hpp"

// The main preprocessing method that hashes the model image into 2D hash map
// Calculates the new coordinates of each corner in the model image according to the reference sets and stores them by hashing the granulated coordinates
void preprocess(std::vector<cv::Point> corners, Multimap2D& modelMap) {
	std::vector<cv::Point> sortedCorners(corners);
	std::sort(sortedCorners.begin(), sortedCorners.end(), cornerSorterAscending);
	std::vector<cv::Point>::iterator lastReference = sortedCorners.end() - 1;
	for (unsigned int itFirst = 0; itFirst < sortedCorners.size(); itFirst++) {
		for (unsigned int itSecond = itFirst + 1; itSecond < sortedCorners.size(); itSecond++) {
			Eigen::Vector2d first(sortedCorners.at(itFirst).x, sortedCorners.at(itFirst).y);
			Eigen::Vector2d second(sortedCorners.at(itSecond).x, sortedCorners.at(itSecond).y);
			Eigen::Vector2d e1 = second - first;
			double distance = e1.norm();
			if (distance <= REFERENCE_SET_DISTANCE) {
				Eigen::Vector2d origin = (first + second) / 2;
				e1.normalize();
				Eigen::Matrix2d rotation90ccw;
				rotation90ccw << 0, -1, 1, 0;
				Eigen::Vector2d e2 = rotation90ccw * e1;
//				std::cout << "Model granulate:" << std::endl;
				for (unsigned int it = 0; it < sortedCorners.size(); it++) {
					Eigen::Vector2i result = Eigen::Vector2i::Zero();
					Eigen::Vector2d transformed = Eigen::Vector2d::Zero();
					Eigen::Vector2d coordinates(sortedCorners.at(it).x, sortedCorners.at(it).y);
					findTransformedCoordinates(e1, e2, distance, origin, coordinates, transformed); // Calculate the transformed coordinates of the atom
					// TODO Determine granularity threshold, currently = 1.0
					granulate(result, transformed, GRANULARITY);// Granulate the result
					modelMap.emplace(HashKeyModel(result), HashEntryModel(itFirst, itSecond, it));//insert the transformed coordinates as a key with the value being the itFirst, itSecond and it
				}
			}
			else {
				continue;
			}
		}
	}
}
