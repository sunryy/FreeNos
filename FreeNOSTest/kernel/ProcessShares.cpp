#include "ProcessShares.h"

#include "intel/pc/System.h"
#include "MemoryChannel.h"
#include "List.h"
#include "ListIterator.h"
#include "SplitAllocator.h"
#include "ProcessEvent.h"

#warning merge with Process please


ProcessShares::ProcessShares(ProcessID pid){
	m_pid = pid;
	m_memory = ZERO;
	m_kernelChannel = new MemoryChannel;
}

ProcessShares::~ProcessShares(){
	ProcessManager *procs=Kernel::instance
}