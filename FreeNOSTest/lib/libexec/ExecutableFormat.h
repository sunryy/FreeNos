#pragma once
#include "Memory.h"
#include "Types.h"

//Entry point of a program
typedef Address EntryPoint;

//Forward declaration.
class ExecutableFormat;

//Confirms if we understand the given format.
typedef ExecutableFormat *FormatDetector(u8 *image, Size size);

//Abstraction class of various executable formats.
class ExecutableFormat{
public:
	//memory region.
	typedef struct Region{
		Address virt;
		Size size;
		Memory::Access access;
		u8 *data;
	}
	Region;

	//Result code
	enum Result
	{
		Success,
		NotFound,
		InvalidFormat,
		OutOfMemory
	};

	//Class constructor.
	ExecutableFormat(u8 *image, Size size);

	//Class destructor.
	virtual ~ExecutableFormat();

	//Memory regions a program needs at runtime.
	virtual Result regions(Region *regions, Size *count) = 0;

	//Lookup the program entry point.
	virtual Result entry(Address *entry) = 0;

	//Find a ExecutableFormat which can handle the given format.
	static Result find(u8 *image, Size size, ExecutableFormat **fmt);

protected:
	u8 *m_image;
	Size m_size;
};