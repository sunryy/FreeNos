#include "string.h"
#include "ctype.h"

int strcasecmp(const char *dest, const char *src)
{
	while (*dest && *src &&(tolower((int)*dest) == tolower((int)*src)))
	{
		dest++;
		src++;
	}
	return (tolower((int)*dest) - tolower((int)*src));
}