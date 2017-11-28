#pragma once
#include "intel/pc/System.h"

//Prototype for user applications. Copies virtual memory between two processes.
inline Error VMCopy(ProcessID proc, API::Operation how, Address ours,
	Address theirs, Size sz)
{
	return trapKernel5(API::VMCopyNumber, proc, how, ours, theirs, sz);
}

extern Error VMCopyHandler(ProcessID proc, API::Operation how, Address ours, Address theirs, Size sz);