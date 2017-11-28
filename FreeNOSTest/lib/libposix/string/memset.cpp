#include "string.h"
void *memset(void *dest, int ch, size_t count){
	char *temp;
	for (temp = (char *)dest; count != 0; count--)
	{
		*temp++ = ch;
	}
	return (dest);
}