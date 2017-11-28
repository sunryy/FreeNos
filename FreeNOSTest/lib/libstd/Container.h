#pragma once
#include "Types.h"
#include "Macros.h"

/**
*Container provide access to stored items.
*/
class Container{
public:
	/**
	*Constructor
	*/
	Container();

	/**
	*Destructor.
	*/
	virtual ~Container();

	/**
	* Returns the maximum size of this Container.
	*
	* @returns size The maximum size of this Container.
	*/
	virtual Size size() const = 0;

	/**
	* Returns the number of items inside the Container.
	* @return Number of items inside the Container.
	*/
	virtual Size count() const = 0;

	virtual void clear() = 0;

	virtual bool isEmpty()const;

	virtual bool reserve(Size size);

	virtual bool shrink(Size size);

	virtual Size squeeze();

	virtual bool resize(Size size);
};