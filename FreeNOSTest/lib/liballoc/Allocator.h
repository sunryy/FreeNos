#pragma once
#ifndef __ASSEMBLER__

#include "Macros.h"
#include "Types.h"

//Memory Allocator.
//This class defines an abstract memory allocator.
class Allocator
{
public:
	//Allocation results.
	enum Result
	{
		Success	= 0,
		InvalidAddress,
		InvalidSize,
		InvalidAlignment,
		OutOfMemory
	};

	//Class constructor.
	Allocator();

	//Class destructor.
	virtual ~Allocator();

	//Makes the given Allocator the default.
	static void setDefault(Allocator *alloc);

	//Retrive the currently default Allocator.
	static Allocator* getDefault();

	//Set parent allocator.
	void setParent(Allocator* parent);

	//Set allocation alignment.
	Result setAlignment(Size size);

	//Set allocation base.
	Result setBase(Address addr);

	//Get memory size.
	virtual Size size() = 0;

	//Get memory available.
	virtual Size available() = 0;

	//Allocate memory.
	virtual Result allocate(Size *size, Address *addr, Size align = ZERO) = 0;

	//Release memory.
	virtual Result release(Address addr) = 0;

protected:
	//Align memory address.
	Address aligned(Address addr, Size boundary);

	//Our parent Allocator, if any.
	Allocator *m_parent;

	//Allocation memory alignment.
	Size m_alignment;

	//Allocation base address
	Address m_base;
};

#ifndef __HOST__
//@name Dynamic memory allocation.
//Allocate new memory.
inline void* operator new(__SIZE_TYPE__ sz)
{
	Address addr;
	if (Allocator::getDefault()->allocate((Size *)&sz, &addr) == Allocator::Success)
	{
		return (void *)addr;
	}
	else
	{
		return (void *)NULL;
	}
}

//Allocate memory for an array.
inline void *operator new[](__SIZE_TYPE__ sz)
{
	Address addr;
	if (Allocator::getDefault()->allocate((Size *)&sz, &addr) == Allocator::Success)
	{
		return (void *)addr;
	}
	else
	{
		return (void *)NULL;
	}
}

//Free memory back to the current Allocator.
inline void operator delete(void *mem)
{
	Allocator::getDefault()->release((Address)mem);
}

//Uses the Heap class to free memory, with the delete[] operator.
inline void operator delete[](void *mem)
{
	Allocator::getDefault()->release((Address)mem);
}

//@name Absolute memory allocation.
//@{

//Let the new() operator return the given memory address.
inline void* operator new(__SIZE_TYPE__ sz, Address addr)
{
	return (void *)addr;
}

//@}
#endif //__HOST__

//@}

#endif //__ASSEMBLER__