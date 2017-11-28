#pragma once
#include "intel/pc/System.h"
#include "Config.h"
#include "Kernel.h"

//Forward declaration.
struct SystemInformation;
class BitAllocator;

//Prototype for user applications.Retrieves system information.
inline Error SystemInfo(SystemInformation *info)
{
	return trapKernel1(API::SystemInfoNumber, (Address)info);
}

//Kernel prototype.
extern Error SystemInfoHandler(SystemInformation *info);

//System information structure.
typedef struct SystemInformation
{
	//Ctr
	SystemInformation()
	{
		SystemInfo(this);
	}

	//System version.
	ulong version;

	//Boot commandline.
	char cmdline[64];

	//Total and available memory in bytes.
	Size memorySize, memoryAvail;

	//Core Identifier
	uint coreId;

	//BootImage physical address
	Address bootImageAddress;
	//BootImage size
	Size bootImageSize;
	
	Address coreChannelAddress;
	Size coreChannelSize;

	//TImer counter
	uint timerCounter;

}
SystemInformation;
