#pragma once
#include "Types.h"
#include "Macros.h"
#include "String.h"
#include "string.h"
#include "limits.h"

#define FILE_DESCRIPTOR_MAX 1024

//Abstracts a file which is opened by a user process.
class FileDescriptor{
public:
	FileDescriptor()
	{
		mount = 0;
		path[0] = ZERO;
		position = 0;
		open = false;
	}

	FileDescriptor(const FileDescriptor &fd){
		mount = fd.mount;
		position = fd.position;
		open = fd.open;
		strlcpy(path, fd.path, PATH_MAX);
	}

	bool operator == (const FileDescriptor &fd) const {
		return fd.mount == mount && strcmp(path, fd.path) == 0;
	}

	bool operator != (const FileDescriptor &fd) const{
		return !(fd.mount == mount && strcmp(path, fd.path) == 0);
	}

	//FileSystem or device server on which this file was opened.
	ProcessID mount;
	//Unique identifier, used by a device driver(minor device ID).
	Address identifier;

	//Path to the file.
	char path[PATH_MAX];

	//State of the file descriptor.
	bool open;

	//Current position indicator.
	Size position;
};