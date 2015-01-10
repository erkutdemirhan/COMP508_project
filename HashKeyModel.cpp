/*
 * HashKeyModel.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#include "HashKeyModel.hpp"

HashKeyModel::HashKeyModel() {
	this->position = Eigen::Vector2i::Zero();
}

HashKeyModel::HashKeyModel(Eigen::Vector2i _position) {
	this->position = _position;
}

HashKeyModel::~HashKeyModel() {

}

Eigen::Vector2i HashKeyModel::getPosition() const {
	return this->position;
}

void HashKeyModel::setPosition(Eigen::Vector2i _position) {
	this->position = _position;
}

bool HashKeyModel::operator==(HashKeyModel const& other) const {
	return this->position == other.getPosition();
}

std::size_t hash_value(HashKeyModel const& key) {
	std::size_t seed = 0;
	boost::hash_combine(seed, (int) key.position(0));
	boost::hash_combine(seed, (int) key.position(1));
	return seed;
}

std::ostream& operator<<(std::ostream& os, const HashKeyModel& key) {
	os << key.getPosition().transpose();
	return os;
}

