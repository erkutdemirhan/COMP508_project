// Author: Deniz Demircioglu
// The preprocessor component that hashes the model image into a hashmap

#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <cv.h>
#include <algorithm>

#include "parameters.h"
#include "HashKeyModel.hpp"
#include "HashEntryModel.hpp"
#include "helperMethods.hpp"

void preprocess(std::vector<cv::Point> corners, Multimap2D& modelMap);

#endif
