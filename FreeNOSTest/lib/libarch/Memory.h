#pragma once
#include "Types.h"
#include "BitOperations.h"

namespace Memory
{
	//Memory access flags.
	typedef enum Access
	{
		None = 0,
		Readable = 1 << 0,
		Writable = 1 << 1,
		Executable = 1<< 2,
		User	 = 1 << 3,
		Uncached	=1 << 4,
		InnerCached	= 1 << 5,
		OuterCached	= 1 << 6,
		Device		= 1 << 7
	}
	Access;

	//Memory range.
	typedef struct Range
	{
		Address virt;	//Virtual address.
		Address phys;	//Physical address.
		Size size;	//Size in number bytes.
		Access access;	//Page access flags.
	}
	Range;
}