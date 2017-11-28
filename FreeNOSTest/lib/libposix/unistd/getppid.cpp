#include "intel/pc/System.h"
#include "unistd.h"

pid_t getppid(){
	return ProcessCtl(SELF, GetParent);
}