#include "string.h"
#include "unistd.h"

int gethostname(char *name, size_t namelen){
	strlcpy(name, "localhost", namelen);
	return 0;
}