#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

int fclose(FILE *stream)
{
	//Close and free.
	close(stream->fd);
	free(stream);
	//Success.
	errno = 0;
	return 0;
}