#pragma once
#include "intel/pc/System.h"
#include "Types.h"
#include "Allocator.h"

//Minimum size required to allocate.
#define  PAGEALLOC_MINIMUM (PAGESIZE * 2)

//Allocates virtual memory using the memory server.
class PageAllocator :public Allocator
{
	/**
	* Class constructor.
	*
	* @param base Starting address to allocate.
	* @param size Maximum size in bytes.
	*/
	PageAllocator(Address start, Size size);

	/**
	* Copy constructor.
	*
	* @param p PageAllocator instance pointer.
	*/
	PageAllocator(PageAllocator *p);

	/**
	* Get base address.
	*
	* Returns the first address of the allocated memory region.
	*
	* @return Start address.
	*/
	Address base();

	/**
	* Get memory size.
	*
	* @return Size of memory owned by the Allocator.
	*/
	virtual Size size();

	/**
	* Get memory available.
	*
	* @return Size of memory available by the Allocator.
	*/
	virtual Size available();

	/**
	* Allocate memory.
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
	* @param addr Points to memory previously returned by allocate().
	* @return Result value.
	*
	* @see allocate
	*/
	virtual Result release(Address addr);


private:
	//Start of the allocated memory region.
	Address m_base;

	//Maximum size to allocate.
	Size m_size;

	//total number of bytes allocated.
	Size m_allocated;
};