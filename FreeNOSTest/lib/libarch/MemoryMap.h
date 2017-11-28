#pragma once
#include "Memory.h"

#define MEMORYMAP_MAX_REGIONS 7

//Describes virtual memory map layout
class MemoryMap
{
public:
	//Memory regions.
	typedef enum Region
	{
		KernelData, //kernel program data from libexec
		kernelPrivate, //Kernel dynamic memory mappings.
		UserData,	//User program data from libexec
		UserHeap,	//User heap
		UserStack,	//User Stack
		UserPrivate,	//User private dynamic memory mappings
		UserShare,	//User shared dynamic memory mappings
	}
	Region;

	//Constructor.
	MemoryMap();

	//Copy Constructor.
	MemoryMap(const MemoryMap &map);

	//Get memory range for the given region.
	Memory::Range range(Region region);

	//Set memory range for the given region.
	void setRange(Region region, Memory::Range range);

protected:
	//Memory ranges.
	Memory::Range m_regions[MEMORYMAP_MAX_REGIONS];
};