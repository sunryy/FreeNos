#pragma once
#include "Types.h"
#include "Macros.h"
#include "ProcessShares.h"

enum ProcessEventType
{
	InterruptEvent,
	ShareCreated,
	ShareRemoved,
	ProcessTerminated
};

//Represents a process which may run on the host.
typedef struct ProcessEvent 
{
	ProcessEventType type;
	Size number;
	ProcessShares::MemoryShare share;
};