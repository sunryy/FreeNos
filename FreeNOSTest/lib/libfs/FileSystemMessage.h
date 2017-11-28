#include "intel/pc/System.h"
#include "Types.h"
#include "ChannelMessage.h"
#include "FileType.h"
#include "FileMode.h"
#include "FileStat.h"

//Actions which may be performed on the filesystem.
typedef enum FileSystemAction
{
	CreateFile = 0,
	ReadFile,
	WriteFile,
	StatFile,
	DeleteFile
}
FileSystemAction;

//FileSystem IPC message.
typedef struct FileSystemMessage :public ChannelMessage
{
	//Assignment operator.
	void operator = (FileSystemMessage *m)
	{
		type = m->type;
		identifier = m->identifier;
		from = m->from;
		action = m->action;
		result = m->result;
		buffer = m->buffer;
		size = m->size;
		offset = m->offset;
		userID = m->userID;
		groupID = m->groupID;
		deviceID = m->deviceID;
		mode = m->mode;
		stat = m->stat;
		path = m->path;
		filetype = m->filetype;
	}

	/**
	* @brief Comparison operator.
	* @param m Other FileSystemMessage to compare with.
	* @return True if equal, false otherwise.
	*/
	bool operator == (FileSystemMessage *m)
	{
		return this->from == m->from &&
			this->action == m->action;
	}

	//Source of the message
	ProcessID from;

	//Action to perform
	FileSystemAction action;

	//Result code.
	Error result;

	//Points to a buffer for I/O.
	char *buffer;

	//Size of the buffer.
	Size size;

	//Offset in the file for I/O.
	Size offset;

	//path name of the file.
	char *path;

	//User ID and group ID.
	u16 userID, groupID;

	//Filetype.
	FileType filetype;

	//File mode permissions.
	FileMode mode;

	//File Statictics.
	FileStat *stat;

	//Device major/minor numbers.
	DeviceID deviceID;
}
FileSystemMessage;