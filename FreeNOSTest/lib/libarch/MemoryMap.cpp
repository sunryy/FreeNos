#include "MemoryMap.h"

MemoryMap::MemoryMap()
{
	setRange(KernelData, map.m_regions[KernelData]);
	setRange(KernelPrivate, map.m_regions[KernelPrivate]);
	setRange(UserData, map.m_regions[UserData]);
	setRange(UserHeap, map.m_regions[UserHeap]);
	setRange(UserStack, map.m_regions[UserStack]);
	setRange(UserPrivate, map.m_regions[UserPrivate]);
	setRange(UserShare, map.m_regions[UserShare]);
}

MemoryMap::MemoryMap(const MemoryMap &map)
{

}

Memory::Range MemoryMap::range(MemoryMap::Region region)
{
	return m_regions[region];
}

void MemoryMap::setRange(Region region, Memory::Range range)
{
	m_regions[region] = range;
}