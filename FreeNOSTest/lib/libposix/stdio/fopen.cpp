#include "fcntl.h"
#include "sys/types.h"

#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

FILE *fopen(const char *filename, const char *mode){
	FILE *f;
	//Handle the file stream request.
	switch (*mode)
	{
		//Read.
	case 'r':
		f = (FILE *)malloc(sizeof(FILE));
		f->fd = open(filename, ZERO);
		return f;
		//Unsupported.
	default:
		break;
	}

	//Sorry, not available yet!
	errno = ENOTSUP;
	return (FILE*)NULL;
}