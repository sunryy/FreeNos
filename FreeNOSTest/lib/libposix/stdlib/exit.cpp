#include "intel/pc/System.h"
#include "stdlib.h"

extern C void exit(int status)
{
	//Request immediate termination
	ProcessCtl(SELF, KillPID, status);
}