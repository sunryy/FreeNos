#include "string.h"
#include "ctype.h"

int strncasecmp(const char *dest, const char *src, size_t count){
	while (*dest && *src && tolower(*dest) == tolower(*src) && count)
	{
		if (--count)
		{
			dest++, src++;
		}
	}
	return (tolower(*dest) - tolower(*src));
}