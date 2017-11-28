#pragma once

#include "File.h"
#include "FileSystemMessage.h"
#include "Types.h"
#include "LinnFileSystem.h"
#include "LinnInode.h"
#include "IOBuffer.h"
#include "errno.h"

/**
* Represents a file on a mounted LinnFS filesystem.
*/
class LinnFile : public File
{
public:

	/**
	* Constructor function.
	* @param fs LinnFS filesystem pointer.
	* @param inode Inode pointer.
	*/
	LinnFile(LinnFileSystem *fs, LinnInode *inode);

	/**
	* Destructor function.
	*/
	virtual ~LinnFile();

	/**
	* @brief Read out the file.
	*
	* @param buffer Input/Output buffer to write bytes to.
	* @param size Number of bytes to copy at maximum.
	* @param offset Offset in the file to start reading.
	* @return Number of bytes read, or Error number.
	*
	* @see IOBuffer
	*/
	virtual Error read(IOBuffer & buffer, Size size, Size offset);

private:

	/** Filesystem pointer. */
	LinnFileSystem *fs;

	/** Inode pointer. */
	LinnInode *inode;
};



