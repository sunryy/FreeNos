#include "System.h"
#include "FileSystemMessage.h"
#include "FileType.h"
#include "Runtime.h"
#include "errno.h"
#include "sys/stat.h"

int creat(const char *path, mode_t mode)
{
	FileSystemMessage msg;
	ProcessID mnt = findMount(path);

	//Fill in the message.
	msg.filetype = ChannelMessage::Request;
	msg.action = CreateFile;
	msg.path = (char *)path;
	msg.filetype = RegularFile;
	msg.mode = (FileMode)(mode & FILEMODE_MASK);

	//Ask FileSystem to create the file for us.
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
	//Report result.
	return msg.result == ESUCCESS ? 0 : -1;
}