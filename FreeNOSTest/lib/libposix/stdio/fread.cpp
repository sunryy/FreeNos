#include "unistd.h"
#include "sys/types.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream)
{
	size_t num = 0, i;
	char *buf = (char *)ptr;

	//Read items.
	for (i = 0; i < nitems; i++)
	{
		num += read(stream->fd, buf, size);
		buf += size;
	}
	//Done.
	return num;
}