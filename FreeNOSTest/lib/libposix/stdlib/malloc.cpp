#include "sys/types.h"
#include "stdlib.h"
#include "errno.h"

extern C void *malloc(size_t size){
	errno = 0;
	return (void *) new char[size];
}