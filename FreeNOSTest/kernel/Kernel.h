#pragma once
#include "Macros.h"
#include "Types.h"
#include "Singleton.h"
#include "BootImage.h"
#include "Memory.h"
#include "CoreInfo.h"
#include "Process.h"
#include "ProcessManager.h"

//Forward declarations.
class API;
class SplitAllocator;
class IntController;
class Timer;
class CPUState;

//Function which is called when the CPU is interrupted.
typedef void InterruptHandler(struct CPUState *state, ulong param);

//Interrupt hook class.
typedef struct InterruptHook
{
	InterruptHook(InterruptHandler *h, ulong p) :handler(h), param(p)
	{

	}

	//Comparision operator.
	bool operator == (InterruptHook *i){
		return handler == i->handler && param == i->param;
	}


	//Executed at time of interrupt.
	InterruptHandler * handler;

	//Passed to the handler.
	ulong param;
}
InterruptHook;

//kernel implementation.
class Kernel :public Singleton<Kernel>
{
public:
	//Result codes.
	enum Result
	{
		Success,
		InvalidBootImage,
		ProcessError
	};

	Kernel(CoreInfo *info);

	//Initialize heap.
	static Error heap(Address base, Size size);

	//Get physical memory allocator.
	SplitAllocator * getAllocator();

	//Get process manager
	ProcessManager * getProcessManager();

	//Get API
	API *getAPI();

	//Get the Current MMU context.
	MemoryContext* getMemoryContext();

	//Get CoreInfo.
	CoreInfo *getCoreInfo();

	Timer *getTimer();

	//Execute the kernel.
	int run();

	//Enable or disable an hardware interrupt (IRQ).
	void enableIRQ(u32 irq, bool enabled);

	//hooks a function to an hardware interrupt.
	virtual void hookIntVector(u32 vec, InterruptHandler h, ulong p);

	//Execute an iterrupt handler.
	virtual void executeIntVector(u32 vec, CPUState *state);

	//Loads the boot image.
	virtual Result loadBootImage();


private:
	//Load a boot pragram.
	virtual Result loadBootProcess(BootImage *image, Address imagePAddr, Size index);

protected:
	//Physical memory allocator.
	SplitAllocator *m_alloc;

	//Process Manager
	ProcessManager *m_procs;

	//API handlers object
	API *m_api;

	//CoreInfo object for this core.
	CoreInfo *m_coreInfo;

	//Interrupt handlers.
	Vector<List<InterruptHook *> *> m_interrupts;

	//Interrupt Controller.
	IntController *m_intControl;

	//Timer device.
	Timer *m_timer;
};