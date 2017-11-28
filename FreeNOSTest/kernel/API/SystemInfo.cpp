#include "SystemInfo.h"

#include "intel/pc/System.h"
#include "Config.h"
#include "Kernel.h"
#include "SplitAllocator.h"
#include "CoreInfo.h"

Error SystemInfoHandler(SystemInformation *info)
{
	SplitAllocator *memory = Kernel::instance->getAllocator();
	CoreInfo *core = Kernel::instance->getCoreInfo();

	DEBUG("");

	//TODO: Verify memory access
	//Fill in our current information
	info->version = VERSIONCODE;
	info->memorySize = memory->size();
	info->memoryAvail = memory->available();
	info->coreId = core->coreId;

	info->bootImageAddress = core->bootImageAddress;
	info->bootImageSize = core->bootImageSize;
	info->timerCounter = core->timerCounter;
	info->coreChannelAddress = core->coreChannelAddress;
	info->coreChannelSize = core->coreChannelSize;

	MemoryBlock::copy(info->cmdline, coreInfo.kernelCommand, 64);
	return API::Success;
}

