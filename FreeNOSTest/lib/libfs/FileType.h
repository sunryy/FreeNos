#pragma once
//Number of bits needed to store a FileType.
#define FILETYPE_BITS	3

//Masker value for all FileTypes.
#define FILETYPE_MASK	7

//Convert from a (host system's)POSIX struct stat into a FileType.
#define FILETYPE_FROM_ST(st)	\
	({   \
	FileType t = UnknownFile;	\
	\
	switch ((st)->st_mode & S_IFMT)	\
	{	\
	case S_IFBLK:  t = BlockDeviceFile; break;	\
	case S_IFCHR:  t = CharacterDeviceFile; break; \
	case S_IFIFO:  t = FIFOFile; break; \
	case S_IFREG:  t = RegularFile; break; \
	case S_IFDIR:  t = DirectoryFile; break; \
	case S_IFLNK:  t = SymlinkFile; break; \
	case S_IFSOCK: t = SocketFile; break; \
	default: break; \
	}	\
	t;	\
	})

//All possible filetypes.
typedef enum FileType
{
	RegularFile = 0;
	DirectoryFile = 1;
	BlockDeviceFile = 2;
	CharacterDeviceFile = 3;
	SymlinkFile = 4;
	FIFOFile = 5;
	SocketFile = 6;
	UnknownFile = 7;
};