#include "VMCtl.h"

#include "intel/pc/System.h"
#include "SplitAllocator.h"
#include "ProcessID.h"

Error VMCtlHandler(ProcessID procID, MemoryOperation op, Memory::Range *range){
	ProcessManager *procs=Kernel::instance
}