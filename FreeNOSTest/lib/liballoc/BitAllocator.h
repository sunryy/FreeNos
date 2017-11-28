#pragma once
#include "BitArray.h"
#include "Types.h"
#include "Memory.h"
#include "Allocator.h"

//Bit memory allocator.
class BitAllocator :public Allocator
{
public:
	//Constructor function.
	BitAllocator(Memory::Range range, Size chunkSize);

	//Get chunk size.
	Size chunkSize();

	//Get total size.
	virtual Size size();

	//Get available memory.
	virtual Size available();

	//Get base memory address.
	Address base();


	/**
	* Get allocation BitArray.
	*
	* @return BitArray object pointer.
	*/
	BitArray * getBitArray();

	/**
	* Allocate memory.
	*
	* @param size Size of memory to allocate.
	* @param addr Address allocated.
	* @param align Alignment of the required memory or use
	*              ZERO for chunksize. Must be a multiple
	*              of the chunksize.
	* @return Result value.
	*/
	virtual Result allocate(Size *size, Address *addr, Size align = ZERO);

	/**
	* Allocate memory.
	*
	* @param size Size of memory to allocate.
	* @param addr Address allocated.
	* @param align Alignment of the required memory or use
	*              ZERO for chunksize. Must be a multiple
	*              of the chunksize.
	* @param allocStart Allocation address to start searching at.
	* @return Result value.
	*/
	Result allocate(Size *size, Address *addr, Size align = ZERO, Address allocStart = 0);

	/**
	* Allocate address.
	*
	* @param addr Allocate a specific address.
	* @return Result value.
	*/
	Result allocate(Address addr);

	/**
	* Check if a chunk is allocated.
	*
	* @return True if allocated, false otherwise.
	*/
	bool isAllocated(Address page);

	/**
	* Release memory chunk.
	*
	* @param chunk The memory chunk to release.
	* @return Result value.
	*/
	virtual Result release(Address chunk);

private:
	//Marks which chunks are (un)used.
	BitArray m_array;

	//Start of memory region.
	Address m_base;

	//Size of each chunk.
	Size m_chunkSize;
};