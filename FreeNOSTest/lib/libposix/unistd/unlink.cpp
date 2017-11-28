#include "unlink.h"

#include "intel/pc/System.h"
#include "FileSystemMessage.h"
#include "errno.h"
#include "Runtime.h"
#include "unistd.h"

int unlink(const char *path){
	FileSystemMessage msg;
	ProcessID mnt = findMount(path);

	//Ask for the inlink.
	if (mnt)
	{
		msg.type = ChannelMessage::Request;
		msg.action = DeleteFile;
		msg.path = (char *)path;
		msg.from = SELF;
		ChannelClient::instance->syncSendReceive(&msg, mnt);

		//Set error number.
		errno = msg.result;
	}
	else
	{
		errno = ENOENT;
	}
	//Done.
	return errno == ESUCCESS ? 0 : (off_t)-1;
}

