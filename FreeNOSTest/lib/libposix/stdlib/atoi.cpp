#include "String.h"
#include "stdlib.h"

extern C int atoi(const char *nptr)
{
	String s = nptr;
	return s.toLong();
}