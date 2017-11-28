#pragma once

#include "Types.h"
#include "index.h"

//Networking packet queue implementation.
class NetworkQueue
{
public:
	//Represents a network packet
	typedef struct Packet
	{
		Size size;
		u8 *data;
		const bool operator == (const struct Packet &pkt)const
		{
			return pkt.size == size && pkt.data == data;
		}
		const bool operator != (const struct Packet &pkt)const
		{
			return pkt.size != size || pkt.data != data;
		}
	}Packet;

	//Ctr
	NetworkQueue(Size packetSize, Size headerSize = 0, Size queueSize = 8);

	//Dtr
	virtual ~NetworkQueue();

	//Set default packet header size
	void setHeaderSize(Size size);

	/**
	* Get unused packet
	*/
	Packet * get();

	/**
	* Put unused packet back.
	*/
	void release(Packet *packet);

	/**
	* Enqueue packet with data.
	*/
	void push(Packet *packet);

	/**
	* Retrieve packet with data.
	*/
	Packet * pop();

private:
	//Contains unused packets
	Index<Packet> m_free;

	//Contains packets with data
	Index<Packet> m_data;

	//Size of each packet
	Size m_packetSize;

	//Size of physical hardware header.
	Size m_packetHeader;
};

