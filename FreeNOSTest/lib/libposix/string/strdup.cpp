#include "sys/types.h"
#include "stdlib.h"
#include "string.h"

char *strdup(const char *str){
	size_t siz;
	char *copy;

	siz = strlen(str) + 1;
	if ((copy = (char *)malloc(siz))==NULL)
	{
		return (char *)NULL;
	}
	(void)memcpy(copy, str, siz);
	return (copy);
}