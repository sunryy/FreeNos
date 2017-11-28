#pragma once
#include "Types.h"

//Abstracts an iteration process.
template<class T> class Iterator
{
public:
	//Destructor.
	virtual ~Iterator() {}

	/**
	* Restart iteration from the beginning.
	*/
	virtual void reset() = 0;

	/**
	* Check if there is more to iterate.
	*
	* @return true if more items, false if not.
	*/
	virtual bool hasNext() const = 0;

	/**
	* Check if there is a current item.
	*
	* @return True if the iterator has a current item, false otherwise.
	*/
	virtual bool hasCurrent() const = 0;

	/**
	* Get the current item read-only.
	*
	* @return Reference to the next item.
	*/
	virtual const T & current() const = 0;

	/**
	* Get the current item modifiable.
	*
	* @return Reference to the next item.
	*/
	virtual T & current() = 0;

	/**
	* Fetch the next item modifiable.
	* This function first fetches the next item
	* and then updates the current item pointer to that item.
	*
	* @return Reference to the next item.
	*/
	virtual T & next() = 0;

	/**
	* Remove the current item from the underlying Container.
	*
	* @return True if removed successfully, false otherwise.
	*/
	virtual bool remove() = 0;

	/**
	* Increment operator.
	* This function first increment the current item
	* and then updates the next item pointer.
	*/
	virtual void operator ++(int num) = 0;
};