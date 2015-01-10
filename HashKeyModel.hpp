/*
 * HashKeyModel.h
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#ifndef HASHKEYMODEL_HPP_
#define HASHKEYMODEL_HPP_

#include <boost/functional/hash.hpp>
#include <Eigen/Core>

class HashKeyModel {
private:
	Eigen::Vector2i position;	// the position vector of origin of the new reference frame
public:
	HashKeyModel();
	HashKeyModel(Eigen::Vector2i _position);
	virtual ~HashKeyModel();
	Eigen::Vector2i getPosition() const;
	void setPosition(Eigen::Vector2i _position);
	bool operator==(HashKeyModel const& other) const;
	friend std::size_t hash_value(HashKeyModel const& p);
	friend std::ostream& operator<<(std::ostream& os, const HashKeyModel& key);
};

#endif /* HASHKEYMODEL_HPP_ */
