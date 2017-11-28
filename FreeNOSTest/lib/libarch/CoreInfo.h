#pragma once
#define KERNEL_PATHLEN 64

//TODO: needed by IntelBoot16.S.
//TODO: warning depends on sizeof(Memory::Acess) which is an enum
#define COREINFO_SIZE (KERNEL_PATHLEN + (8*4) + (4*4) + (4*4))
#ifndef __ASSEMBLER__
#include "Macros.h"
#include "Types.h"
#include "Memory.h"

typedef struct CoreInfo 
{
	uint booted;
	uint coreId;
	Memory::Range memory;

	//Kernel entry point
	Address kernelEntry;

	//Kernel memory range
	Memory::Range kernel;

	//Kernel command
	char kernelCommand[KERNEL_PATHLEN];

	Address bootImageAddress;
	Address bootImageSize;
	Address coreChannelAddress;
	Size coreChannelSize;

	//Arch-specific timer counter.
	uint timerCounter;

	//TODO: fix this in libstd. we should not need to do this for Index
	bool operator == (const struct CoreInfo & info) const
	{
		return false;
	}
	bool operator != (const struct CoreInfo & info) const
	{
		return true;
	}
}
CoreInfo;

//Local CoreInfo instance.
//Architecture is responsible for filling the 
//CoreInfo struct instance for the core on which it executes.
extern CoreInfo coreInfo;

#endif //__ASSEMBLER__