#pragma once
#include "Types.h"

/**
* Objects which can be compared to each other.
*/
template <Class T>class Comparable
{
public:

	/**
	* Class destructor.
	*/
	virtual ~Comparable() {}

	/**
	* Test if an object is equal to an other object.
	*/
	virtual bool equals(const T &t) const
	{
		return compareTo(t) == 0;
	}

	//Compare this Comparable to the given Comparable.
	//This function checks whether this Comparable is equal to, less, or greater
	//then the given Comparable.
	virtual int compareTo(const T &t) const = 0;
};