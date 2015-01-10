/*
 * HashEntryModel.hpp
 *
 *  Created on: Jan 10, 2015
 *      Author: ddemircioglu
 */

#ifndef HASHENTRYMODEL_HPP_
#define HASHENTRYMODEL_HPP_

#include <vector>
#include <cv.h>

class HashEntryModel {
private:
	int itFirst;	// the index of the first corner forming the reference
	int itSecond;	// the index of the second corner forming the reference
	int itCorner;	// the index of the corner for which coordinates is recalculated

public:
	HashEntryModel();
	HashEntryModel(unsigned int _itFirst, unsigned int _itSecond, unsigned int _itCorner);
	virtual ~HashEntryModel();
	unsigned int getItFirst() const;
	void setItFirst(unsigned int _itFirst);
	unsigned int getItSecond() const;
	void setItSecond(unsigned int _itSecond);
	unsigned int getItCorner() const;
	void setItCorner(unsigned int _itCorner);
	HashEntryModel& operator=(const HashEntryModel& rhs);
	bool operator==(HashEntryModel const& other) const;
	friend std::ostream& operator<<(std::ostream& os, const HashEntryModel& entry);
};

#endif /* HASHENTRYMODEL_HPP_ */
