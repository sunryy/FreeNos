#pragma once
#include "host/include/System.h"
#include "API.h"
#include "Types.h"
#include "FileSystemMessage.h"
#include "FileType.h"
#include "FileMode.h"
#include "IOBuffer.h"
#include "errno.h"

//Abstracts a file present on a FileSystem.
class File
{
public:
	//Ctr
	File(FileType type = RegularFile, UserID uid = ZERO, GroupID gid = ZERO);

	//Dtr
	virtual ~File();

	/**
	* Retrieve our filetype.
	* @return FileType object.
	*/
	FileType getType();

	/**
	* Get the number of times we are opened by a process.
	* @return Open count.
	* @see openCount
	*/
	Size getOpenCount();

	/**
	* Attempt to open a file.
	* @param msg Describes the open request.
	* @param pid Process Identity to serve us from. May be changed
	*            to redirect to other servers.
	* @param ident Identity to be filled in the FileDescriptor.
	* @return Error code status.
	*/
	virtual Error open(ProcessID *pid, Address *ident);

	/**
	* @brief Attempt to close a file.
	*
	* @return Error code status.
	*/
	virtual Error close();

	/**
	* @brief Read bytes from the file.
	*
	* @param buffer Input/Output buffer to output bytes to.
	* @param size Number of bytes to read, at maximum.
	* @param offset Offset inside the file to start reading.
	* @return Number of bytes read on success, Error on failure.
	*/
	virtual Error read(IOBuffer & buffer, Size size, Size offset);

	/**
	* Write bytes to the file.
	*
	* @param buffer Input/Output buffer to input bytes from.
	* @param size Number of bytes to write, at maximum.
	* @param offset Offset inside the file to start writing.
	* @return Number of bytes written on success, Error on failure.
	*/
	virtual Error write(IOBuffer & buffer, Size size, Size offset);

	/**
	* Retrieve file statistics.
	*
	* @param st Buffer to write statistics to.
	*/
	virtual Error status(FileSystemMessage *msg);

protected:

	//Type of this file.
	FileType m_type;

	//Access permissions.
	FileModes m_access;

	//Size of the file, in bytes.
	Size m_size;

	//Number of times the File has been opened by a process.
	Size m_openCount;

	//Owner of the file.
	UserID m_uid;

	//Group of the file.
	GroupID m_gid;
	
	//Device major/minor ID.
	DeviceID m_deviceId;

};