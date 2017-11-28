#pragma once

#include "Vector.h"
#include "Macros.h"
#include "Process.h"

class Timer;

//Responsible for deciding which Process may execute on the CPU(s).
class Scheduler{
public:
	//ctr
	Scheduler();

	//Set timer to use
	void setTimer(Timer *timer);

	//Select the next process to run.
	virtual Process *select(Vector<Process *> *procs, Process *idle);

private:
	//Contains last used index for scheduling.
	Size m_index;

	//Points to the TImer to use for sleep timeouts
	Timer *m_timer;
};
