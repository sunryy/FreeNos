#pragma once

#include "Types.h"

#define LINN_DIRENT_PER_BLOCK(sb) \
	((sb)->blockSize / sizeof(LinnDirectoryEntry))

//Length of the name field in an directory entry.
#define LINN_DIRENT_NAME_LEN 59


//Struct of an directory entry in LinnFS.
typedef struct LinnDirectoryEntry
{
	//Inode number.
	le32 inode;

	//Type of file, as an FileType.
	u8 type;

	//File name. Null terminated.
	char name[LINN_DIRENT_NAME_LEN];
}
LinnDirectoryEntry;