#include "string.h"
int strncmp(const char *dest, const char* src, size_t count){
	while (*dest && *src && *dest == *src && count)
	{
		if ((--count)
		{
			dest++, src++;
		}
	}
	return (*dest - *src);
}