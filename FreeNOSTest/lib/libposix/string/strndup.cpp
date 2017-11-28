#include "stdlib.h"
#include "string.h"
#include "sys/types.h"

char *strndup(const char *s, size_t size)
{
	size_t bytes;
	char *buff;
	//Fetch input string length.
	bytes = strlen(s);

	//calculates bytes to allocate.
	if (bytes > size)
	{
		bytes = size;
	}
	//Allocate buffer.
	if ((buff=(char *)malloc(bytes + 1)) == NULL)
	{
		return (char *)NULL;
	}
	//Copy input into new buffer.
	memcpy(buff, s, bytes + 1);

	//Null terminate.
	buff[bytes] = 0;
	//Done.
	return buff;
}