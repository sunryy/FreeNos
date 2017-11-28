#include "System.h"
#include "FileSystemMessage.h"
#include "Runtime.h"
#include "errno.h"
#include "sys/stat.h"

int mkdir(const char *path, mode_t mode)
{
	FileSystemMessage msg;
	ProcessID mnt = findMount(path);

	//Fill message.
	msg.type = ChannelMessage::Request;
	msg.action = CreateFile;
	msg.path = (Char *)path;
	msg.mode = mode;
	msg.filetype = DirectoryFile;

	//Ask the FileSystem to create it.
	if (mnt)
	{
		ChannelClient::instance->syncSendReceive(&msg, mnt);
		//Set errno
		errno = msg.result;
	}
	else
	{
		errno = ENOENT;
	}
	//Success.
	return msg.result == ESUCCESS ? 0 : -1;
}