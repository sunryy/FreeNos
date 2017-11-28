#include "intel/pc/System.h"
#include "FileSystemMessage.h"
#include "Runtime.h"
#include "errno.h"
#include "unistd.h"

ssize_t read(int fildes, void *buf, size_t nbyte){
	FileSystemMessage msg;
	FileDescriptor *fd = (FileDescriptor *)getFiles()->get(fildes);

	//Read the file.
	if (fd)
	{
		msg.filetype = ChannelMessage::Request;
		msg.action = ReadFile;
		msg.path = fd->path;
		msg.buffer = (char *)buf;
		msg.size = nbyte;
		msg.offset = fd->position;
		msg.from = SELF;
		msg.deviceID.minor = fd->identifier;
		ChannelClient::instance->syncSendReceive(&msg, fd->mount);

		//Did we read something?
		if (msg.result >= 0)
		{
			fd->position += msg.result;
			return msg.result;
		}
		//Set error code
		errno = msg.result;
	}
	else
	{
		errno = ENOENT;
	}
	return -1;
}