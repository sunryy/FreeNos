#include "CoreServer.h"

#include "intel/pc/System.h"
#include "ExecutableFormat.h"
#include "CoreServer.h"
#include "stdio.h"
#include "string.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"

#include "intel/IntelMP.h"

const char *CoreServer::kernelPath = "/boot/kernel";

CoreServer::CoreServer()
:ChannelServer<CoreServer, FileSystemMessage>(this)
{
	m_numRegions = 0;
	m_kernel = ZERO;
	m_kernelImage = ZERO;
	m_coreInfo = ZERO;

#ifdef INTEL
	m_cores = ZERO;
	m_toMaster = ZERO;
	m_fromMaster = ZERO;
	m_toSlave = ZERO;
	m_fromSlave = ZERO;
#endif

	//Register IPC handlers
	addIPCHandler(ReadFile, &CoreServer::getCoreCount);
}

