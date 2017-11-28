#pragma once
#include "Types.h"
#include "MemoryMap.h"
#include "Process.h"
#include "Scheduler.h"

//Maximum number of processes.
#define MAX_PROCS 1024
//Represents a process which may run on the host.
class ProcessManager
{
public:
	//ctr
	ProcessManager(Scheduler * scheduler);

	//dtr
	virtual ~ProcessManager();

	//Get scheduler object
	Scheduler * getScheduler();

	//Create and add a new Process.
	Process * create(Address entry, const MemoryMap &map);

	//Retrieve a Process by a it's ID.
	Process *get(ProcessID id);

	//Remove a Process
	void remove(Process *proc, uint exitStatus = 0);

	//Schedule next process to run.
	void schedule(Process *proc = ZERO);

	//Set the idle process.
	void setIdle(Process *proc);

	//Current process running. NULL If no process running yet.
	Process * current();

	//Previous process running.
	Process * previous();

	//Retrieve the process table.
	Vector<Process *> * getProcessTable();

private:
	//all known Processes.
	Vector<Process *> m_procs;

	//Object which selects processes to run.
	Scheduler *m_scheduler;

	//Currently executing process
	Process* m_current;

	//Previous process executing
	Process *m_previous;

	//Idle process
	Process *m_idle;

};