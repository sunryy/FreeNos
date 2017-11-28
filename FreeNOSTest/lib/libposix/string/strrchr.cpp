#include "string.h"

char *strrchr(const char *s, int c)
{
	char *last = (char *)NULL;
	for (; *s; s++)
	{
		if (*s == c)
		{
			last = (char *)s;
		}
	}
	return last;
}