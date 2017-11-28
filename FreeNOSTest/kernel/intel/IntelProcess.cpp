#include "IntelProcess.h"
#include "intel/pc/System.h"
#include "MemoryBlock.h"
#include "Memory.h"
#include "SplitAllocator.h"
#include "intel/IntelPaging.h"
#include "IntelProess.h"


IntelProcess::IntelProcess(ProcessID id, Address entry, bool privileged, const MemoryMap &map)
:Process(id, entry, privileged, map)
{

}

Process::Result IntelProcess::initialize()
{
	Address stackSize, stackAddr;
	Memory::Range range;
	CPUState *regs;
	u16 dataSel = m_privileged ? KERNEL_DS_SEL : USER_DS_SEL;
	u16 codeSel = m_privileged ? KERNEL_CS_SEL : USER_CS_SEL;

	//Create MMU context
	m_memoryContext = new IntelPaging(
		&m_map,
		Kernel::instance->getAllocator());
	if (!m_memoryContext)
	{
		return OutOfMemory;
	}

	//User stack (high memory).
	range = m_map.range(MemoryMap::UserStack);
	range.access = Memory::Readable | Memory::Writable | Memory::User;
	if (Kernel::instance->getAllocator()->allocate(&range.size, &range.phys)!=Allocator::Success)
	{
		return OutOfMemory;
	}

	if (m_memoryContext->mapRange(&range)!=MemoryContext::Success)
	{
		return MemoryMapError;
	}
	//Kernel stack (low memory).
	stackSize = PAGESIZE;
	if (Kernel::instance->getAllocator()->allocateLow(stackSize, &stackAddr)!=Allocator::Success)
	{
		return OutOfMemory;
	}
	stackAddr = (Address)Kernel::instance->getAllocator()->toVirtual(stackAddr);
	m_kernelStackBase = stackAddr + stackSize;
	setKernelStack(m_kernelStackBase - sizeof(CPUState)
									 - sizeof(IRQRegs0)
									 - sizeof(CPURegs));

	//Fill kernel stack with initial (user) registers to restore
	//loadCoreState: struct CPUState
	regs = (CPUState *)m_kernelStackBase - 1;
	MemoryBlock::set(regs, 0, sizeof(CPUState));
	regs->seg.ss0 = KERNEL_DS_SEL;
	regs->seg.fs = dataSel;
	regs->seg.gs = dataSel;
	regs->seg.es = dataSel;
	regs->seg.ds = dataSel;
	regs->regs.ebp = m_userStack;
	regs->regs.esp0 = m_kernelStack;
	regs->irq.eip = m_entry;
	regs->irq.cs = codeSel;
	regs->irq.eflags = INTEL_EFLAGS_DEFAULT |
		INTEL_EFLAGS_IRQ;
	regs->irq.esp3 = m_userStack;
	regs->irq.ss3 = dataSel;

	//restoreState: iret
	IRQRegs0 *irq = (IRQRegs0 *)regs - 1;
	irq->eip = (Address)loadCoreState;
	irq->cs = KERNEL_CS_SEL;
	irq->eflags = INTEL_EFLAGS_DEFAULT;

	//restoreState : popa
	CPURegs *pusha = (CPURegs *)irq - 1;
	MemoryBlock::set(pusha, 0, sizeof(CPURegs));
	pusha->ebp = m_kernelStackBase - sizeof(CPURegs);
	pusha->esp0 = pusha->ebp;
	//Finalize with generic initialization
	return Process::initialize();
}


IntelProcess::~IntelProcess()
{
	//Release the kernel stack memory page
	Kernel::instance->getAllocator()->release(m_kernelStackBase - KernelStackSize);
}

void IntelProcess::execute(Process *previous)
{
	IntelProcess *p = (IntelProcess *)previous;
	//Reload Task State Register (with kernel stack for interrupts)
	kernelTss.esp0 = m_kernelStackBase;
	//ltr(KERNE_TSS_SEL);

	//Activate the memory context of this process
	m_memoryContext->activate();
	
	//Switch kernel stack (includes saved userspace registers)
	switchCoreState(p ? &p->m_kernelStack : ZERO, m_kernelStack);

}