#pragma once
#include "Types.h"
#include "Macros.h"
#include "Allocator.h"

//Minimum power of two for a pool size.
#define  POOL_MIN_POWER 2

//Maximum power of two size  a pool can be.
#define POOL_MAX_POWER 32

//Allocate this  many blocks per default for the given size.
#define POOL_MIN_COUNT(size)	\
	(64 / (((size) / 1024) + 1)) > 0 ?	\
	(64 / (((size) / 1024) + 1)) : 1

//Calculates the number of bytes needed in a bitmap, 
//to hold the specified number of elements.
#define BITMAP_NUM_BYTES(count)	\
	((count / 8) + 1)

//Memory pool contains pre-allocated blocks of a certain size (power of two).
typedef struct MemoryPool 
{
	//Marks the appropriate bits in the free and used block bitmap.
	Address allocate(){
		Address *ptr;
		Size num = count / sizeof(Address);

		//At least one.
		if (!num)
		{
			num++;
		}

		//Scan bitmap as fast as possible.
		for (Size i = 0; i < num; i++)
		{
			//Point to the correct offset.
			ptr = (Address *)(&blocks) + i;

			//Any blocks free?
			if (*ptr !=(Address)~ZERO)
			{
				//Find the first free bit.
				for (Size bit = 0; bit < sizeof(Address)* 8; bit++)
				{
					if (!(*ptr & 1 << bit))
					{
						*ptr |= (1 << bit);
						free--;
						return addr + (((i*sizeof(Address)* 8) + bit) * size);
					}
				}
			}
		}
		//Out of Memory
		return ZERO;
	}

	//Unmarks the appropriate bit for th given address.
	void release(Address a){
		Size index = (a - addr) / size / 8;
		Size bit = (a - addr) / size % 8;
		free++;
		blocks[index] &= ~(1 << bit);
	}

	//Points to the next pool of this sie(if any).
	MemoryPool *next;

	//Memory address allocated to this pool.
	Address addr;

	//Size of each object in the pool.
	Size size;

	//Number of blocks in the pool .
	Size count;

	//Free blocks left.
	Size free;

	//Bitmap which represents free and used blocks.
	u8 blocks[];
};

//Memory allocator which uses pools.
class PoolAllocator : public Allocator
{
public:
	//Ctr
	PoolAllocator();

	//Get memory size.
	virtual Size size();

	*Get memory available.
		*
		* @return Size of memory available by the Allocator.
		* /
		virtual Size available();

	/**
	* Allocate memory.
	*
	* @param size Amount of memory in bytes to allocate on input.
	*             On output, the amount of memory in bytes actually allocated.
	* @param addr Output parameter which contains the address
	*             allocated on success.
	* @param align Alignment of the required memory or use ZERO for default.
	* @return Result value.
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
	//Creates a new MemoryPool instance.
	MemoryPool *newPool(Size index, Size cnt);

	//Array of memory pools. Index represents the power of two.
	MemoryPool *m_pools[POOL_MAX_POWER];
};