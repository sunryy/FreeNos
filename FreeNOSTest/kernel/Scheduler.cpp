#include "Scheduler.h"

#include "Log.h"

Scheduler::Scheduler()
{
	DEBUG("");
	m_index = 0;
	m_timer = 0;
}

void Scheduler::setTimer(Timer *timer)
{
	m_timer = timer;
}

Process *Scheduler::select(Vector<Process *> *procs, Process *idle)
{
	Size size = procs->size();

	for (Size i = 0; i < size; i++)
	{
		//Increment process index
		m_index = (m_index + 1) % size;
		//Pick the process
		Process *p = procs->at(m_index);

		if (p)
		{
			Process::State state = p->getState();

			//Wakeup the process if its sleeptimer expired
			if (state==Process::Sleeping && m_timer->isExpired(p->getSleepTimer()))
			{
				p->wakeup();

				//Select this process if it wants to run
				if (p!=idle && (state == Process::Ready || state == Process::Running))
				{
					return p;
				}
			}
		}
		
	}
}
