#pragma once
#include "Types.h"
#include "Factory.h"
#include "ExecutableFormat.h"
#include "ELFHeader.h"

//Executable and Linkable Format (ELF).
class ELF :public ExecutableFormat{
public:
	//Ctr
	ELF(u8 *image, Size size);

	/**
	* Class destructor.
	*/
	virtual ~ELF();

	/**
	* Reads out segments from the ELF program table.
	*
	* @param regions Memory regions to fill.
	* @param count Maximum number of memory regions on input.
	*              Actual number of memory regions on output.
	* @return Result code.
	*/
	virtual Result regions(Region *regions, Size *count);

	/**
	* Lookup the program entry point.
	*
	* @param entry Program entry point on output.
	* @return Result code.
	*/
	virtual Result entry(Address *entry);

	/**
	* Read ELF header from memory.
	*/
	static Result detect(u8 *program, Size size, ExecutableFormat **fmt);

};