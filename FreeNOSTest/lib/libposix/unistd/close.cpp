#include "intel/pc/System.h"
#include "FileSystemMessage.h"
#include "Runtime.h"
#include "errno.h"
#include "unistd.h"

int close(int fildes)
{
	Vector<FileDescriptor> *fds = getFiles();
	FileDescriptor *fd = ZERO;

	if ((fd = (FileDescriptor *)fds->get(fildes)) == ZERO || !fd->open)
	{
		errno = ENOENT;
		return -1;
	}
	fd->open = false;
	return 0;
}