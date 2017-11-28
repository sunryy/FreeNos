#include "dirent.h"
#include "fcntl.h"
#include "unistd.h"

int closedir(DIR *dirp){
	//Close file handle.
	close(dirp->fd);

	//Free buffers.
	delete dirp->buffer;
	delete dirp;

	//Success.
	return 0;
}