#pragma once
#include "Types.h"
#include "limits.h"

//Maximum number of mounted filesystems.
#define FILESYSTEM_MAXMOUNTS	16

//Represents a mounted filesystem.
typedef struct FileSystemMount{
	//Path of the mount.
	char path[PATH_MAX];

	//Server which is responsible for the mount.
	ProcessID procID;

	//Mount options.
	ulong options;
}
FIleSystemMount;