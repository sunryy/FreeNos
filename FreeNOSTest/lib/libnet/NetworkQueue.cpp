#include "NetworkQueue.h"

NetworkQueue::NetworkQueue(Size packetSize, Size headerSize /* = 0 */, Size queueSize /* = 8 */)
{
	m_packetSize = packetSize;
	m_packetHeader = headerSize;
	for (Size i = 0; i < queueSize; i++)
	{
		Packet *packet = new Packet;
		packet->size = m_packetHeader;
		packet->data = new u8[packetSize];
		m_free.insert(*packet);
	}
}

NetworkQueue::~NetworkQueue()
{
	for (Size i = 0; i < m_free.size(); i++)
	{
		Packet *p = (Packet *)m_free.get(i);
		if (p)
		{
			delete p->data;
			delete p;
		}
	}
}

void NetworkQueue::setHeaderSize(Size size)
{
	m_packetHeader = size;
}

NetworkQueue::Packet * NetworkQueue::get()
{
	for (Size i = 0; i < m_free.size(); i++)
	{
		Packet *p = (Packet *)m_free.get(i);
		if (p)
		{
			p->size = m_packetHeader;
			m_free.remove(i);
			return p;
		}
	}
	return ZERO;
}

void NetworkQueue::release(NetworkQueue::Packet *packet)
{
	packet->size = m_packetHeader;
	m_free.insert(*packet);
}

void NetworkQueue::push(NetworkQueue::Packet *packet)
{
	m_data.insert(*packet);
}

NetworkQueue::Packet * NetworkQueue::pop()
{
	for (Size i = 0; i < m_data.size(); i++)
	{
		Packet *p = (Packet *)m_data.get(i);
		if (p)
		{
			m_data.remove(i);
			return p;
		}
	}
	return ZERO;
}
