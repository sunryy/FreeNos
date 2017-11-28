#pragma once
#include "Types.h"

//Number of bits required for all FileModes.
#define FILEMODE_BITS	9

//Masker value for all FileMode values.
#define FILEMODE_MASK	0777

//Converts an (host system's) POSIX struct st into a FileMode.
#define FILEMODE_FROM_ST(st)	\
	(FileMode)((st)->st_mode & FILEMODE_MASK)

//File access permissions.
typedef enum FileMode
{
	OwnerR = 0400,
	OwnerW = 0200,
	OwnerX = 0100,
	OwnerRW = 0600,
	OwnerRX = 0500,
	OwnerRWX = 0700,
	GroupR = 0040,
	GroupW = 0020,
	GroupX = 0010,
	GroupRW = 0060,
	GroupRX = 0050,
	GroupRWX = 0070,
	OtherR = 0004,
	OtherW = 0002,
	OtherX = 0001,
	OtherRW = 0006,
	OtherRX = 0005,
	OtherRWX = 0007,

}
FileMode;

//Multiple FileMode values combined.
typedef u16 FileModes;