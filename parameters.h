/*
 * parameters.h
 *
 *  Created on: Jan 9, 2015
 *      Author: ddemircioglu
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <boost/unordered_map.hpp>
#include "./HashKeyModel.hpp"
#include "./HashEntryModel.hpp"
#include "./HashKeyScene.hpp"

#define GRANULARITY 1.0	// How grained the model hash map should be
#define REFERENCE_SET_DISTANCE 20.0	// How far can another atom be in a reference set
#define VOTING_THRESHOLD 7	// The minimum number of votes needed for a reference set to be considered
#define PURIFICATION_DISTANCE 5.0 // The distance that will be used to purify corners based on their distance

typedef boost::unordered_multimap<HashKeyModel, HashEntryModel> Multimap2D;	// the hash map structure for the model map (preprocessing)
typedef boost::unordered_map<HashKeyScene, std::vector<std::pair<unsigned int, unsigned int> > > Map2D;	// the hash map structure for the voting process (matching)

#endif /* PARAMETERS_H_ */
