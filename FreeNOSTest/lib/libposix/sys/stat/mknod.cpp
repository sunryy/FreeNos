#include "System.h"
#include "FileSystemMessage.h"
#include "FileType.h"
#include "FileMode.h"
#include "Runtime.h"
#include "errno.h"
#include "sys/stat.h"

int mknod(const char *path, mode_t mode, dev_t dev)
{
	FileSystemMessage msg;
	ProcessID mnt = findMount(path);
	//Fill in the message.
	msg.type = ChannelMessage::Request;
	msg.action = CreateFile;
	msg.path = (char *)path;
	msg.deviceID = dev;
	msg.filetype = (FileType)((mode >> FILEMODE_BITS) &FILETYPE_MASK);
	msg.mode = (FileModes)(mode &FILEMODE_MASK);

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