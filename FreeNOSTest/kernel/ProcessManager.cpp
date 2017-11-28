#include "ProcessManager.h"
#include "intel/pc/System.h"
#include "Log.h"

//TODO: replace Vector with an Index..
ProcessManager::ProcessManager(Scheduler *scheduler)
:m_procs(MAX_PROCS)
{
	DEBUG("m_procs = " << MAX_PROCS);
	m_scheduler = scheduler;
	m_current = ZERO;
	m_previous = ZERO;
	m_idle = ZERO;
}

Scheduler * ProcessManager::getScheduler()
{
	return m_scheduler;
}

Process *ProcessManager::create(Address entry, const MemoryMap &map){
	Process *proc = new Arch::Process(m_procs.count(), entry, false, map);

	//insert to the process table
	if (proc && proc->initialize() == Process::Success)
	{
		m_procs.insert(proc);
		return proc;
	}
	return ZERO;
}


Process * ProcessManager::get(ProcessID id)
{
	// TODO: replace with an Index to make this more easy.
	Process **p = (Process **)m_procs.get(id);
	return p ? *p : ZERO;
}

void ProcessManager::remove(Process *proc, uint exitStatus){
	if (proc==m_previous)
	{
		m_previous = ZERO;
	}

	if (proc == m_idle)
	{
		m_idle = ZERO;
	}

	if (proc == m_current)
	{
		m_current = ZERO;
	}

	//Wakeup any Processes which are waiting for this Process
	Size size = m_procs.size();

	for (Size i = 0; i < size; i++)
	{
		if (m_procs[i] != ZERO && 
			m_procs[i]->getState() == Process::Waiting &&
			m_procs[i]->getWait() == proc->getID())
		{
			m_procs[i]->setState(Process::Ready);
			m_procs[i]->setWait(exitStatus);
		}
	}

	//Remove process from administration
	m_procs[proc->getID()] = ZERO;
	//Free the process memory
	delete proc;
}

void ProcessManager::schedule(Process *proc)
{
	//If needed , let the scheduler select a new process
	if (!proc)
	{
		proc = m_scheduler->select(&m_procs, m_idle);

		//if no process ready, let us idle.
		if (!proc)
		{
			proc = m_idle;
		}
	}

	if (!proc)
	{
		FATAL("no process found to run!"); for (;;);
	}

	//Only execute if its a different process
	if (proc != m_current)
	{
		m_previous = m_current;
		m_current = proc;
		if (m_previous && m_previous->getState() == Process::Running)
		{
			m_previous->setState(Process::Ready);
		}
		proc->setState(Process::Running);
		proc->execute(m_previous);
	}
}


Process * ProcessManager::current()
{
	return m_current;
}

Process * ProcessManager::previous()
{
	return m_previous;
}

void ProcessManager::setIdle(Process *proc)
{
	m_idle = proc;
}

Vector<Process *> * ProcessManager::getProcessTable()
{
	return &m_procs;
}
