/*
 * HashEntryModel.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#include "HashEntryModel.hpp"

HashEntryModel::HashEntryModel() {
	this->itFirst = 0;
	this->itSecond = 0;
	this->itCorner = 0;
}

HashEntryModel::HashEntryModel(unsigned int _itFirst, unsigned int _itSecond, unsigned int _itCorner) {
	this->itFirst = _itFirst;
	this->itSecond = _itSecond;
	this->itCorner = _itCorner;
}

HashEntryModel::~HashEntryModel() {

}

unsigned int HashEntryModel::getItFirst() const {
	return this->itFirst;
}

void HashEntryModel::setItFirst(unsigned int _itFirst) {
	this->itFirst = _itFirst;
}

unsigned int HashEntryModel::getItSecond() const {
	return this->itSecond;
}

void HashEntryModel::setItSecond(unsigned int _itSecond) {
	this->itSecond = _itSecond;
}

unsigned int HashEntryModel::getItCorner() const {
	return this->itCorner;
}

void HashEntryModel::setItCorner(unsigned int _itCorner) {
	this->itCorner = _itCorner;
}

HashEntryModel& HashEntryModel::operator=(const HashEntryModel& rhs) {
	if (this != &rhs) {
		this->itFirst = rhs.itFirst;
		this->itSecond = rhs.itSecond;
		this->itCorner = rhs.itCorner;
	}
	return *this;
}

bool HashEntryModel::operator==(HashEntryModel const& other) const {
	return this->itFirst == other.itFirst && this->itSecond == other.itSecond && this->itCorner == other.itCorner;
}

std::ostream& operator<<(std::ostream& os, const HashEntryModel& entry) {
	os << "First iterator: " << entry.itFirst << std::endl;
	os << "Second iterator: " << entry.itSecond << std::endl;
	os << "Corner iterator: " << entry.itCorner  << std::endl;
	return os;
}

