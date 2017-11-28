#include "string.h"
char *strerror(int errnum){
	return error_map[-errnum % -ELAST];
}