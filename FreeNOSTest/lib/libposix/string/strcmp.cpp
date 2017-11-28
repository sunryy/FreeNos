#include "string.h"
char *strcmp(const char *dest, const char *src){
	while (*dest && *src && *dest == *src)
	{
		dest++;
		src++;
	}
	return (*dest - *src);
}