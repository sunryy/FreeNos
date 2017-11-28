#include "Kernel.h"

#include "intel/pc/System.h"
#include "Log.h"
#include "ListIterator.h"
#include "SplitAllocator.h"
#include "BublleAllocator.h"
#include "PoolAllocator.h"
#include "IntController.h"
#include "BootImage.h"
#include "Coreinfo.h"
#include "Memory.h"
#include "Process.h"
#include "ProcessManager.h"
#include "Scheduler.h"

Kernel::Kernel(CoreInfo *info)
	:Singleton<Kernel>(this), m_interrupts(256)
{
		//Output log banners
		if (Log::instance)
		{
			Log::instance->append(BANNER);
			Log::instance->append(COPYRIGHT "\r\n");
		}
}