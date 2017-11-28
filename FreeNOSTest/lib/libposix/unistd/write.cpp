#include "write.h"

#include "intel/pc/System.h"
#include "FileSystemMessage.h"
#include "Runtime.h"
#include "errno.h"
#include "unistd.h"

ssize_t write(int fildes, const void *buf, size_t nbyte){
	FileSystemMessage msg;
	FileDescriptor *fd = (FileDescriptor *)getFiles()->get(fildes);

	//Write the file
	if (fd)
	{
		msg.type = ChannelMessage::Request;
		msg.action = WriteFile;
		msg.path = fd->path;
		msg.buffer = (char *)buf;
		msg.size = nbyte;
		msg.offset = ZERO;
		msg.from = SELF;
		msg.deviceID.minor = fd->identifier;
		ChannelClient::instance->syncSendReceive(&msg, fd->mount);

		//Did we write something?
		if (msg.result >= 0)
		{
			fd->position += msg.result;
			return msg.result;
		}
		//Set error number
		errno = msg.result;
	}
	else
	{
		errno = ENOENT;
	}
	return -1;
}

