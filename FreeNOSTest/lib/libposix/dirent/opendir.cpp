#include "intel/pc/System.h"
#include "FileType.h"
#include "Directory.h"
#include "errno.h"
#include "dirent.h"
#include "fcntl.h"
#include "unistd.h"
#include "sys/stat.h"

DIR *opendir(const char *dirname)
{
	Dirent *dirent;
	DIR *dir;
	int fd;
	struct stat st;
	Error e;

	//First stat the directory.
	if (stat(dirname, &st) < 0)
	{
		return (ZERO);
	}
	//Try to open the directory.
	if ((fd = open(dirname, ZERO)) < 0)
	{
		return (ZERO);
	}
	//Allocate DIrents.
	dirent = new Dirent[1024];
	memset(dirent, 0, 1024 * sizeof(Dirent));

	//Allocate DIR object.
	dir = new DIR;
	dir->fd = fd;
	dir->buffer = new struct dirent[1024];
	memset(dir->buffer, 0, 1024 * sizeof(struct dirent));
	dir->current = 0;
	dir->count = 0;
	dir->eof = false;

	//Read them all.
	if ((e=read(fd, dirent, sizeof(Dirent) *1024)) < 0)
	{
		e = errno;
		closedir(dir);
		errno = e;
		return (ZERO);
	}
	//Fill in the dirent structs.
	for (Size i = 0; i < e / sizeof(Dirent); i++)
	{
		u8 types[] = 
		{
			DT_REG,
			DT_DIR,
			DT_BLK,
			DT_CHR,
			DT_LNK,
			DT_FIFO,
			DT_SOCK,
		};
		strlcpy((dir->buffer)[i].d_name, dirent[i].name, DIRLEN);
		(dir->buffer)[i].d_type = types[dirent[i].type];
	}

	dir->count = e / sizeof(Dirent);
	delete dirent;

	//Set errno.
	errno = ESUCCESS;
	//Success.
	return dir;

}