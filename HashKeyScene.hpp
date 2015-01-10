/*
 * HashKeyScene.h
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#ifndef HASHKEYSCENE_HPP_
#define HASHKEYSCENE_HPP_

#include <boost/functional/hash.hpp>
#include "helperMethods.hpp"
#include "HashEntryModel.hpp"

class HashKeyScene {
private:
	unsigned int itFirst;	// the index of the first corner forming the new reference frame
	unsigned int itSecond;	// the index of the first corner forming the new reference frame
public:
	HashKeyScene();
	HashKeyScene(HashKeyScene& key);
	HashKeyScene(const HashKeyScene& key);
	HashKeyScene(const HashEntryModel& e);
	HashKeyScene(unsigned int _itFirst, unsigned int _itSecond);
	virtual ~HashKeyScene();
	bool operator==(HashKeyScene const& other) const;
	friend std::size_t hash_value(HashKeyScene const& p);	// 2d hash function
};


#endif /* HASHKEYSCENE_HPP_ */
