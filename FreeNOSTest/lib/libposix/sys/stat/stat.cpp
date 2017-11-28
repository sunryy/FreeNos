#include "System.h"
#include "FileSystemMessage.h"
#include "Runtime.h"
#include "errno.h"
#include "Log.h"
#include "sys/stat.h"

int stat(const char *path, struct stat *buf)
{
	FileSystemMessage msg;
	FileStat st;
	ProcessID mnt = findMount(path);

	//File message.
	msg.type = ChannelMessage::Request;
	msg.action = StatFile;
	msg.path = (char*)path;
	msg.stat = &st;

	DEBUG("path = " << (uint)msg.path << " stat = " << (uint)msg.stat);

	//Ask the FileSystem for the information.
	if (mnt)
	{
		ChannelClient::instance->syncSendReceive(&msg, mnt);

		//Copy information into buf
		if (msg.result == ESUCCESS)
		{
			buf->fromFileStat(&st);
		}
		//Set errno
		errno = msg.result;
	}
	else
	{
		errno = msg.result = ENOENT;
	}
	//Success.
	return msg.result == ESUCCESS ? 0 : -1;
}