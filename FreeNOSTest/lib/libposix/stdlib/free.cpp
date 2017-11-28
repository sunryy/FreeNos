#include "sys/types.h"
#include "stdlib.h"
#include "errno.h"

extern C void free(void *ptr){
	delete (char *)ptr;
}