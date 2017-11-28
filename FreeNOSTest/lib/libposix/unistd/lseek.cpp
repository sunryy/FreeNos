#include "lseek.h"

#include "Runtime.h"
#include "errno.h"
#include "unistd.h"

off_t lseek(int fildes, off_t offset, int whence)
{
	FileDescriptor	*fd = (FileDescriptor *)getFiles()->get(fildes);
	//Do we have this file descriptor?
	if (!fd)
	{
		errno = ENOENT;
		return -1;
	}
	//Update the file pointer
	fd->position = offset;
	//Done
	return 0;
}
