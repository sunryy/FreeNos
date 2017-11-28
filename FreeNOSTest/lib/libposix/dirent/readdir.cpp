#include "Macros.h"
#include "dirent.h"

struct dirent *readdir(DIR *dirp){
	if (dirp->current < dirp->count)
	{
		return &dirp->buffer[dirp->current++];
	}
	else
	{
		return (struct dirent *)ZERO;
	}
}