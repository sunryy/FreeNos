#include "VMCopy.h"

#include "MemoryBlock.h"
#include "SplitAllocator.h"

Error VMCopyHandler(ProcessID procID, API::Operation how, Address ours, Address theirs, Size sz)
{
	ProcessManager *procs = Kernel::instance->getProcessManager();
	Process *proc;
	Address paddr, vaddr;
	Size bytes = 0, pageOff, total = 0;

	DEBUG("");

	//Find the corresponding Process
	if (procID == SELF)
	{
		proc = procs->current();
	}
	else if (!(proc = procs->get(procID)))
	{
		return API::NotFound;
	}

	//TODO: Verify memory addresses
	MemoryContext *local = procs->current()->getMemoryContext();
	MemoryContext *remote = proc->getMemoryContext();

	//Keep on going until all memory is processed
	while (total < sz)
	{
		//Update variables.
		if (how == API::ReadPhys)
		{
			paddr = theirs & PAGEMASK;
		}
		else if (remote->lookup(theirs, &paddr) != MemoryContext::Success)
		{
			return API::AccessViolation;
		}
		paddr &= PAGEMASK
			pageOff = theirs & ~PAGEMASK;
		bytes = (PAGESIZE - pageOff) < (sz - total) ?
			(PAGESIZE - pageOff) : (sz - total);

		//Valid address?
		if (!paddr)
		{
			break;
		}
		//Map their address into our local address space
		if (local->findFree(PAGESIZE, MemoryMap::kernelPrivate, &vaddr) != MemoryContext::Success)
		{
			return API::RangeError;
		}
		local->map(vaddr, paddr, Memory::Readable | Memory::Writable);

		//Process the action appropriately.
		switch (how)
		{
		case API::Read:
		case API::ReadPhys:
			MemoryBlock::copy((void *)ours, (void *)(vaddr + pageOff), bytes);
			break;
		case API::Write:
			MemoryBlock::copy((void *)(vaddr + pageOff), (void *)ours, bytes);
			break;
		default:
			break;
		}
		//Unmap
		local->unmap(vaddr);

		//Update counters
		ours += bytes;
		theirs += bytes;
		total += bytes;
	}
	return total;
}

