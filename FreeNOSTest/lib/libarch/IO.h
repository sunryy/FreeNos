#pragma once
#include "Types.h"
#include "Memory.h"

//Generic I/O functions.
class IO
{
public:
	enum Result
	{
		Success,
		MapFailure,
		OutOfMemory
	};

	//Constructor.
	IO();

	//Get I/O base offset.
	uint getBase() const;

	//Set I/O base offset.
	void setBase(uint base);

	//Map I/O address space.
	Result map(Address phys, 
		       Size size = 4096,
			   Memory::Access access=Memory::Readable | Memory::Writable | Memory::User);

	//Unmap I/O address space.
	Result unmap();

protected:
	//I/O base offset is added to each I/O address.
	uint m_base;

	//Memory range for  performing I/O mappings.
	Memory::Range m_range;

};