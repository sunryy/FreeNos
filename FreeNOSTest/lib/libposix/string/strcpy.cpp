#include "string.h"

int strcpy(char *dest, const char *src){
	char *d = dest;
	const char *s = src;
	int count = 0;
	while (*s)
	{
		*(d++) = *(s++);
		count++;
	}
	*(d++) = '\0';
	return (count);
}