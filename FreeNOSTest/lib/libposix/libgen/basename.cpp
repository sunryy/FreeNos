#include "string.h"
#include "libgen.h"

char *basename(char *path)
{
	char *str = path;
	//Point to the last component, if any.
	if ((str = strrchr(path, '/')))
	{
		str++;
	}
	return str;
}