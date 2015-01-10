/*
 * HashKeyScene.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#include "HashKeyScene.hpp"

HashKeyScene::HashKeyScene() {
	this->itFirst = 0;
	this->itSecond = 0;
}

HashKeyScene::HashKeyScene(HashKeyScene& key) {
	this->itFirst = key.itFirst;
	this->itSecond = key.itSecond;
}

HashKeyScene::HashKeyScene(const HashKeyScene& key) {
	this->itFirst = key.itFirst;
	this->itSecond = key.itSecond;
}

HashKeyScene::HashKeyScene(const HashEntryModel& e) {
	this->itFirst = e.getItFirst();
	this->itSecond = e.getItSecond();
}

HashKeyScene::HashKeyScene(unsigned int _itFirst, unsigned int _itSecond) {
	this->itFirst = _itFirst;
	this->itSecond = _itSecond;
}

HashKeyScene::~HashKeyScene() {

}

bool HashKeyScene::operator==(HashKeyScene const& other) const {
	return this->itFirst == other.itFirst && this->itSecond == other.itSecond;
}

std::size_t hash_value(HashKeyScene const& key) {
	std::size_t seed = 0;
	boost::hash_combine(seed, key.itFirst);
	boost::hash_combine(seed, key.itSecond);
	return seed;
}
