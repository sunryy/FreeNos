#include "FileSystemRequest.h"

FileSystemRequest::FileSystemRequest(FileSystemMessage *msg)
{
	m_msg = msg;
	m_ioBuffer = new IOBuffer(&m_msg);
}

FileSystemRequest::~FileSystemRequest()
{
	delete m_ioBuffer;
}

FileSystemMessage *FileSystemRequest::getMessage()
{
	return &m_msg;
}

IOBuffer &FileSystemRequest::getBuffer()
{
	return *m_ioBuffer;
}

