#pragma once
#include "Types.h"
#include "Allocator.h"

//Keeps growing allocated memory, and can't actually free memory(hence the name).
class BubbleAllocator : public Allocator
{
public:
	//ctr
	BubbleAllocator(Address start, Size size);

	//Get memory size.
	virtual Size size();

	/**
	* Get memory available.
	*
	* @return Size of memory available by the Allocator.
	*/
	virtual Size available();

	/**
	* Allocate memory
	*
	* @param size Amount of memory in bytes to allocate on input.
	*             On output, the amount of memory in bytes actually allocated.
	* @param addr Output parameter which contains the address
	*             allocated on success.
	* @param align Alignment of the required memory or use ZERO for default.
	* @return New memory block on success and ZERO on failure.
	*/
	virtual Result allocate(Size *size, Address *addr, Size align = ZERO);

	/**
	* Release memory.
	*
	* Does nothing for BubbleAllocator.
	*
	* @param address Points to memory previously returned by allocate().
	*
	* @see allocate
	*/
	virtual Result release(Address addr);

private:
	//Memory region to allocate from.
	u8 *m_start;

	//Current "top" of the growing bubble.
	u8 *m_current;

	//Size of the memory region.
	Size m_size;
};