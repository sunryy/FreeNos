#pragma once
#include "Types.h"
#include "Macros.h"
#include "List.h"
#include "MemoryMap.h"
#include "Timer.h"
#include "Index.h"
#include "ProcessShares.h"
//IPCMessage.h
struct Message;
class MemoryContext;
class MemoryChannel;
struct ProcessEvent;

//Virtual memory address of the array of arguments for new processes.
#define ARGV_ADDR 0x9ffff000

//Maximum size of each argument.
#define ARGV_SIZE 128

//Number of arguments at maximum
#define ARGV_COUNT (PAGESIZE / ARGV_SIZE)

//Represents a process which may run on the host.
class Process
{
public:

	enum Result
	{
		Success,
		MemoryMapError,
		OutOfMemory,
		WakeupPending
	};

	enum State
	{
		Running,
		Ready,
		Stopped,
		Sleeping,
		Waiting
	};

	Process(ProcessID id, Address entry, bool privileged, const MemoryMap &map);

	virtual ~Process();

	//Retrieve our ID number.
	ProcessID getID() const;

	ProcessID getParent() const;

	//Get Wait ID.
	ProcessID getWait() const;


	/**
	* Get sleep timer.
	* @return Sleep timer value.
	*/
	const Timer::Info * getSleepTimer() const;

	/**
	* Get process shares.
	* @return Reference to memory shares.
	*/
	ProcessShares & getShares();

	/**
	* Retrieves the current state.
	* @return Current status of the Process.
	*/
	State getState() const;

	/*
	* Get the address of our page directory.
	* @return Page directory address.
	*/
	Address getPageDirectory() const;

	/**
	* Get the address of the user stack.
	*
	* @return User stack address.
	*/
	Address getUserStack() const;

	/**
	* Get the address of the kernel stack.
	*
	* @return Kernel stack address.
	*/
	Address getKernelStack() const;

	/**
	* Get MMU memory context.
	*
	* @return MemoryContext pointer.
	*/
	MemoryContext * getMemoryContext();

	/**
	* Raise kernel event
	*/
	Result raiseEvent(struct ProcessEvent *event);

	/**
	* Get privilege.
	*
	* @return Privilege of the Process.
	*/
	bool isPrivileged() const;

	/**
	* Puts the Process in a new state.
	* @param st New state of the Process.
	*/
	void setState(State st);

	/**
	* Set parent process ID.
	*/
	void setParent(ProcessID id);

	/**
	* Set Wait ID.
	*/
	void setWait(ProcessID id);

	/**
	* Set sleep timer.
	* @param sleeptimer New sleep timer value.
	*/
	void setSleepTimer(const Timer::Info *sleeptimer);

	/**
	* Set page directory address.
	*
	* @param addr New page directory address.
	*/
	void setPageDirectory(Address addr);

	/**
	* Sets the address of the user stack.
	*
	* @param addr New stack address.
	*/
	void setUserStack(Address addr);

	/**
	* Set the kernel stack address.
	*
	* @param addr New kernel stack address.
	*/
	void setKernelStack(Address addr);

	//Compare two processes.
	bool operator == (Process * proc);

	//Prevent process from sleeping.
	Result wakeup();

	//Stops the process for executing until woken up
	Result sleep(Timer::Info *timer = 0);

	//Initialize the Process.
	virtual Result initialize();

	//Allow the Process to run on the CPU.
	virtual void execute(Process *previous) = 0;

protected:
	//Process Identifier.
	const ProcessID m_id;

	//Parent process
	ProcessID m_parent;

	//Current process status.
	State m_state;

	//Wait for exit of this Process.
	ProcessID m_waitId;

	//Privilege level
	bool m_privileged;

	//Entry point of the program
	Address m_entry;

	//Virtual memory layout
	MemoryMap m_map;

	//MMU memory context
	MemoryContext *m_memoryContext;

	//Page directory
	Address m_pageDirectory;

	//User stack address.
	Address m_userStack;

	//Current kernel stack address (changes during execution).
	Address m_kernelStack;

	//Base kernel stack (fixed)
	Address m_kernelStackBase;

	//Number of wakeup received
	Size m_wakeups;

	//Sleep timer value.
	//if non-zero , set the process in the Ready state
	//when the System timer is greater than this value.
	Timer::Info m_sleepTimer;

	//Contains virtual memory shares between this process and others.
	ProcessShares m_shares;

	//Channel for sending kernel events to the Process
	MemoryChannel *m_kernelChannel;
};