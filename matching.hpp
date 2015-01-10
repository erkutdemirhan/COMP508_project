/*
 * matching.hpp
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#ifndef MATCHING_HPP_
#define MATCHING_HPP_

#include <vector>

#include "helperMethods.hpp"
#include "parameters.h"


void matching(std::vector<cv::Point>& sceneCorners, Multimap2D& modelMap, std::vector<std::vector<std::pair<unsigned int, unsigned int> > >& candidateMatches);



#endif /* MATCHING_HPP_ */
