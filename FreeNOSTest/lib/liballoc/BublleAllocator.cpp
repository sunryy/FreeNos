#include "BublleAllocator.h"

#include "intel/pc/System.h"

BubbleAllocator::BubbleAllocator(Address start, Size size)
{
	m_start = (u8 *)start;
	m_current = (u8 *)start;
	m_size = size;
}

Size BubbleAllocator::size(){
	return m_size;
}

Size BubbleAllocator::available(){
	return m_size - (m_current - m_start);
}

Allocator::Result BubbleAllocator::allocate(Size *sz, Address *addr, Size align){
	Size needed = aligned(*sz, MEMALIGN);

	//Do we still hae enough room?
	if (m_current + needed < m_start + m_size)
	{
		m_current += needed;
		*addr = (Address)(m_current - needed);
		return Success;
	}
	//No more memory available
	return OutOfMemory;
}

Allocator::Result BubbleAllocator::release(Address addr){
	//BubbleAllocator never releases memory
	return InvalidAddress;
}