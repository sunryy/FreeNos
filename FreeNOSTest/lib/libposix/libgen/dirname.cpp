
#include "string.h"
#include "limits.h"
#include "libgen.h"

char *dirname(char *path){
	static char buf[PATH_MAX];
	char *str;
	if (path[0])
	{
		if ((str=strrchr(path, '/')))
		{
			strlcpy(buf, path, (str - path) + 1);
		}
		else
		{
			strlcpy(buf, path, PATH_MAX);
		}
	}
	else
	{
		strlcpy(buf, ".", PATH_MAX);
	}
	return buf;
}