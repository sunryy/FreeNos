#include "DeviceServer.h"

DeviceServer::DeviceServer(const char *path)
:FileSystem(path)
{
	m_interrupts.fill(ZERO);
}

DeviceServer::~DeviceServer(){

}

Error DeviceServer::initialize()
{
	setRoot(new Directory());
}

