#include "string.h"
int strncpy(char *dest, const char *src, size_t sz){
	char *d;
	const char *s;
	int val = 0;
	d = dest;
	s = src;

	while (*s != '\0' && sz != 0)
	{
		*d++ = *s++;
		sz--;
		val++;
	}
	*d++ = '\0';
	return val;
}