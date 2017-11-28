#pragma once

#include "Macros.h"


//Return the last comonent of a pathname.
extern C char *basename(char *path);

//return String pointer to the directory of pathname.
extern C char *dirname(char *path);