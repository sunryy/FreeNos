#include "SplitAllocator.h"
#include "System.h"


SplitAllocator::SplitAllocator(Memory::Range low, Memory::Range high)
:Allocator()
{
	Memory::Range mem = low;
	mem.size += high.size;
	m_alloc = new BitAllocator(mem, PAGESIZE);
	m_low = low;
	m_high = high;
}

SplitAllocator::~SplitAllocator()
{
	delete m_alloc;
}


Size SplitAllocator::size()
{
	return m_alloc->size();
}

Size SplitAllocator::available()
{
	return m_alloc->available();
}


Allocator::Result SplitAllocator::allocate(Size *size, Address *addr, Size align)
{
	Allocator::Result r;
	if ((r=allocateHigh(*size, addr, align)) == Success)
	{
		return r;
	}
	else
	{
		return allocateLow(*size, addr, align);
	}
	
}

Allocator::Result SplitAllocator::allocate(Address addr)
{
	return m_alloc->allocate(addr);
}

Allocator::Result SplitAllocator::allocateLow(Size size, Address *addr, Size align)
{
	return m_alloc->allocate(&size, addr, align, 0);
}

Allocator::Result SplitAllocator::allocateHigh(Size size, Address *addr, Size align)
{
	return m_alloc->allocate(&size, addr, align, m_high.phys - m_alloc->base());
}

Allocator::Result SplitAllocator::release(Address addr)
{
	return m_alloc->release(addr);
}

void * SplitAllocator::toVirtual(Address phys)
{
	return (void *)(phys - m_low.phys);
}
