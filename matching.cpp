/*
 * matching.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#include "matching.hpp"

// The main matching method determining the matches (corner pairs)
//	Vector sceneCorners: Scene corners which will be used for calculation
//	Multimap2D modelMap: The hash map of model corners that holds the required reference set - corner information for voting
// 	std::vector<std::vector<std::pair<unsigned int, unsigned int>>> candidateMatches: The result that holds the candidate matches (corner pair lists) that have more elements than the voting threshold
void matching(std::vector<cv::Point>& sceneCorners, Multimap2D& modelMap, std::vector<std::vector<std::pair<unsigned int, unsigned int> > >& candidateMatches) {
	std::vector<cv::Point> sortedCorners(sceneCorners);
	std::sort(sortedCorners.begin(), sortedCorners.end(), cornerSorterAscending);
	std::vector<cv::Point>::iterator lastReference = sortedCorners.end() - 1;
	for (unsigned int itFirst = 0; itFirst < sortedCorners.size(); itFirst++) {
		for (unsigned int itSecond = itFirst + 1; itSecond < sortedCorners.size(); itSecond++) {
			Map2D votingMap;
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
//				std::cout << "Scene granulate:" << std::endl;
				for (unsigned int it = 0; it < sortedCorners.size(); it++) {
					Eigen::Vector2i result = Eigen::Vector2i::Zero();
					Eigen::Vector2d transformed = Eigen::Vector2d::Zero();
					Eigen::Vector2d coordinates(sortedCorners.at(it).x, sortedCorners.at(it).y);
					findTransformedCoordinates(e1, e2, distance, origin, coordinates, transformed); // Calculate the transformed coordinates of the atom
					// TODO Determine granularity threshold, currently = 1.0
					granulate(result, transformed, GRANULARITY);// Granulate the result

					std::pair<Multimap2D::iterator, Multimap2D::iterator> bound = modelMap.equal_range(HashKeyModel(result));	// Check for hash map entries with the same coordinates
					if (bound.first == modelMap.end() && bound.second == modelMap.end()) {// there is no such reference set
						continue;
					} else {	// there is an entry for these coordinates
						for (Multimap2D::iterator itLocal = bound.first; itLocal != bound.second; itLocal++) {// For all reference sets with this coordinates
							HashKeyScene key(itLocal->second);
							Map2D::iterator sceneIterator = votingMap.find(key);// Check if this has been seen before
							if (sceneIterator == votingMap.end()) {	// there is no entry,  create a new corner pair list and insert into votemap
								sceneIterator = votingMap.insert(std::make_pair(key,std::vector<std::pair<unsigned int, unsigned int> >())).first;
								sceneIterator->second.push_back(std::make_pair(itLocal->second.getItCorner(), it));
							} else {// there is an entry, add the new corner pair to the end of the existing corner pair list (i.e. increase vote count)
								sceneIterator->second.push_back(std::make_pair(itLocal->second.getItCorner(), it));
							}
						}
					}
					//////////////////////////////////////
					for (Map2D::iterator it = votingMap.begin(); it != votingMap.end(); it++) {// For all entries in the vote map
						if (it->second.size() >= VOTING_THRESHOLD) {// Check if there are enough votes
							candidateMatches.push_back(it->second);// insert the corner pair list to the possible results
						} else {
							continue;
						}
					}
				}
			}
			else {
				continue;
			}
		}
	}
}


