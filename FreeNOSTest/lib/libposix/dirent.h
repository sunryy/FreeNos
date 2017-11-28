#pragma once

#include "Macros.h"
#include "Types.h"
#include "sys/types.h"
#include "string.h"



/** The file type is unknown. */
#define DT_UNKNOWN       0

/** This is a named pipe (FIFO). */
#define DT_FIFO          1

/** This is a character device. */
#define DT_CHR           2

/** This is a directory. */
#define DT_DIR           4 

/** This is a block device. */
#define DT_BLK           6

/** This is a regular file. */
#define DT_REG           8

/** This is a symbolic link. */
#define DT_LNK          10

/** This is a Unix domain socket. */
#define DT_SOCK         12

/** Maximum length of a directory entry name. */
#define DIRLEN		64

//Represents a directory entry.
struct dirent 
{
	//Name of entry.
	char d_name[DIRLEN];
	//Type of file.
	u8 d_type;

#ifdef CPP
	//Comparison operator.
	bool operator == (struct dirent *d)
	{
		return strcmp(d->d_name, d_name) == 0 && d->d_type == d_type;
	}
#endif
};

//A type representing a directory stream.
//The DIR type may be an incomplete type.
typedef struct DIR{
	//File descriptor returned by opendir().
	int fd;

	//Input buffer.
	struct dirent *buffer;

	//Index of the current dirent.
	Size current;

	//Number of direct structures in the buffer.
	Size count;

	//End-of-file reached?
	bool eof;
};