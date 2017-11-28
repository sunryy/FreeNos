#include "PageAllocator.h"

#include "intel/pc/System.h"
PageAllocator::PageAllocator(Address start, Size size)
{
	m_base = base;
	m_size = size;
	m_allocated = 0;
}

PageAllocator::PageAllocator(PageAllocator *p){
	m_base = p->m_base;
	m_size = p->m_size;
	m_allocated = p->m_allocated;
}

Address PageAllocator::base()
{
	return m_base;
}

Size PageAllocator::size()
{
	return m_size;
}

Size PageAllocator::available()
{
	return m_size - m_allocated;
}

Allocator::Result PageAllocator::allocate(Size *size, Address *addr, Size align /* = ZERO */)
{
	Memory::Range range;
	//Set return address.
	*addr = m_base + m_allocated;
	//TODO: sanity checks
	Size bytes = *size > PAGEALLOC_MINIMUM ? 
				 *size : PAGEALLOC_MINIMUM;

	//Align to pagesize
	bytes = aligned(bytes, PAGESIZE);
	//Fill in the message.
	range.size = bytes;
	range.access = Memory::User | Memory:Readable | Memory::Writable;
	range.virt = m_base + m_allocated;
	range.phys = ZERO;

	VMCtl(SELF, Map, &range);
	//Clear the pages
	MemoryBlock::set((void*)range.virt, 0, range.size);
	//Update count
	m_allocated += range.size;
	//Success
	*size = range.size;
	return Success;
}

Allocator::Result PageAllocator::release(Address addr)
{
	//TODO: let the heap shrink if possible
	return InvalidAddress;
}