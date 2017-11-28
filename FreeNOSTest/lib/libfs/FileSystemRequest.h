#pragma once

#include "FileSystemMessage.h"
#include "IOBuffer.h"


//Encapsulates a pending FileSystemMessage.
class FileSystemRequest
{
public:
	//Ctr
	FileSystemRequest(FileSystemMessage *msg);

	/**
	* Destructor
	*/
	virtual ~FileSystemRequest();

	/**
	* Get message.
	*/
	FileSystemMessage * getMessage();

	/**
	* Get IOBuffer.
	*/
	IOBuffer & getBuffer();

private:
	//Message that was received
	FileSystemMessage m_msg;

	//Wrapper for doing I/O on the FileSystemMessage buffer.
	IOBuffer *m_ioBuffer;
};

