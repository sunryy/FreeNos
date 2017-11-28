#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"

int snprintf(char *buffer, unsigned int size, const char *fmt, ...)
{
	va_list args;
	int ret;
	va_start(args, fmt);
	ret = vsnprintf(buffer, size, fmt, args);
	va_end(args);
	return (ret);
}