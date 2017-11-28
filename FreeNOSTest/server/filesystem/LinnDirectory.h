#pragma once
#include "FileSystemMessage.h"
#include "Directory.h"
#include "Types.h"
#include "LinnDirectoryEntry.h"
#include "LinnFileSystem.h"
#include "LinnInode.h"
#include "IOBuffer.h"

/**
* Represents an directory on a LinnFS filesystem.
* @see Directory
* @see LinnDirectoryEntry
* @see LinnFileSystem
*/
class LinnDirectory : public Directory
{
public:

	/**
	* Constructor function.
	* @param fs Filesystem pointer.
	* @param inode Inode pointer.
	* @see LinnFileSystem
	* @see LinnInode
	*/
	LinnDirectory(LinnFileSystem *fs, LinnInode *inode);

	/**
	* @brief Read directory entries.
	*
	* @param buffer Input/Output buffer to write bytes to.
	* @param size Number of bytes to copy at maximum.
	* @param offset Offset in the file to start reading.
	* @return Number of bytes read on success, Error on failure.
	*
	* @see IOBuffer
	*/
	virtual Error read(IOBuffer & buffer, Size size, Size offset);

	/**
	* @brief Retrieves a File pointer for the given entry name.
	*
	* This function reads a file from disk corresponding
	* to the LinnInode of the given entry name. It returns
	* an File object associated with that LinnInode.
	*
	* @param name Name of the entry to lookup.
	* @return Pointer to a File if found, or ZERO otherwise.
	*
	* @see File
	* @see LinnInode
	*/
	virtual File * lookup(const char *name);

private:

	/**
	* Retrieve a directory entry.
	* @param dent LinnDirectoryEntry buffer pointer.
	* @param name Unique name of the entry.
	* @return True if successful, false otherwise.
	*/
	bool getLinnDirectoryEntry(LinnDirectoryEntry *dent,
		const char *name);

	/** Filesystem pointer. */
	LinnFileSystem *fs;

	/** Inode which describes the directory. */
	LinnInode *inode;
};