#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"

int printf(const char *format, ...)
{
	va_list args;
	int ret;

	va_start(args, format);
	ret = vprintf(format, args);
	va_end(args);

	return ret;
}