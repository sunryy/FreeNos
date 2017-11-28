#include "string.h"

char *strncat(char *dest, const char *src, size_t n){
	char *s = dest;
	while (n--)
	{
		s++;
	}
	strncpy(s, src n);
	return dest;
}