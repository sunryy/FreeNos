#include "intel/pc/System.h"

//Memory operations which may be used to an argument to VMCtl().
typedef enum MemoryOperation
{
	Map=0,
	UnMap,
	Release,
	LookupVirtual,
	Access,
	RemoveMem,
	AddMem,
	CacheClean
}
MemoryOperation;

//prototype for user applications.Examines and modifies virtual memory pages.
inline Error VMCtl(ProcessID procID, MemoryOperation op, 
				   Memory::Range *range=ZERO){
	return trapKernel3(API::VMCtlNumber, procID, op, (Address)range);
}

extern Error VMCtlHandler(ProcessID procID, MemoryOperation op, Memory::Range *range);