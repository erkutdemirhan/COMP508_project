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
#define REFERENCE_SET_DISTANCE 25.0	// How far can another atom be in a reference set
#define SPHERE_RADIUS 12.5	// The maximum distance at which another atom is concerned for local seed match calculation (both hash map creation and voting)
#define VOTING_THRESHOLD 7	// The minimum number of votes needed for a reference set to be considered
#define TRANSFORMATION_DIFFERENCE 0.01	// The maximum distance between to transformation matrices of seed matches
#define CLUSTERING_RESIDUE_PERCENTAGE 0.20	// The percentage needed for a model-scene atom pair to be considered in the global match
#define EXTENSION_MAXIMUM_ITERATION 5	// The maximum number of iterations that will be performed by cubic matching for extending
#define EXTENSION_DISTANCE_THRESHOLD 3.0 	// The distance threshold used for extension (the maximum distance allowed between pairs of atoms)

typedef boost::unordered_multimap<HashKeyModel, HashEntryModel> Multimap2D;	// the hash map structure for the model map (preprocessing)
typedef boost::unordered_map<HashKeyScene, std::vector<std::pair<unsigned int, unsigned int> > > Map2D;	// the hash map structure for the voting process (matching)
//typedef boost::unordered_map<VotingMapKey, int> VotingMap;	// the hash map structure for the clustering voting (clustering)



#endif /* PARAMETERS_H_ */
