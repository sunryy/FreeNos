#include "string.h"
#include "errno.h"
#include "Runtime.h"
#include "unistd.h"

char *getcwd(char *buf, size_t size){
	//Copy our current working directory.
	memcpy(buf, ** getCurrentDirectory(), size);

	//Set errno.
	errno = ESUCCESS;
	//All done.
	return buf;
}