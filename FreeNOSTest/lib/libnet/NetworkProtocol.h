#pragma once

#include "Directory.h"
#include "Types.h"
#include "NetworkQueue.h"

class NetworkServer;
class NetworkDevice;

//Network protocol abstraction class.
class NetworkProtocol :public Directory
{
public:
	//Ctr
	NetworkProtocol(NetworkServer *server, NetworkDevice *device);

	//Dtr
	virtual ~NetworkProtocol();

	//Get maximum packet size.
	virtual const Size getMaximumPacketSize() const;

	/**
	* Perform initialization.
	*/
	virtual Error initialize() = 0;

	/**
	* Process incoming network packet.
	*
	* @return Error code
	*/
	virtual Error process(NetworkQueue::Packet *pkt, Size offset) = 0;

protected:
	//Network server instance
	NetworkServer *m_server;

	//Network device instance
	NetworkDevice *m_device;
};
