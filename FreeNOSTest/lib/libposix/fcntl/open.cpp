#include "intel/pc/System.h"
#include "FileSystemMessage.h"
#include "Runtime.h"
#include "errno.h"
#include "fcntl.h"
#include "sys/stat.h"

int open(const char *path, int oflag, ...){
	FileSystemMessage msg;
	ProcessID mnt = findMount(path);

	Vector<FileDescriptor> *fds = getFiles();
	FileStat st;

	//Fill message
	msg.type = ChannelMessage::Request;
	msg.action = StatFile;
	msg.path = (char *)path;
	msg.stat = &st;

	//Ask the FileSystem for the file.
	if (mnt)
	{
		ChannelClient::instance->syncSendReceive(&msg, mnt);

		//Refresh mounts and retry, in case the file did not exist
		if (msg.result == ENOENT)
		{
			refreshMounts(0);
			mnt = findMount(path);
			msg.filetype = ChannelMessage::Request;
			ChannelClient::instance->syncSendReceive(&msg, mnt);
		}

		//Set errno
		errno = msg.result;

		if (msg.result == ESUCCESS)
		{
			//Insert into file descriptor table
			for (Size i = 0; i < fds->size(); i++)
			{
				if (!(*fds)[i].open)
				{
					(*fds)[i].open = true;
					strlcpy((*fds)[i].path, path, PATH_MAX);
					(*fds)[i].mount = mnt;
					(*fds)[i].identifier = 0;
					(*fds)[i].position = 0;
					return i;
				}
			}
			//Too many open files
			errno = ENFILE;
		}
	}
	else
	{
		errno=ENOENT:
	}
	return -1;
}