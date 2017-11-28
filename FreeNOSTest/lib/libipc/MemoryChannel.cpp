#include "MemoryChannel.h"
#include "Log.h"
#include "intel/pc/System.h"

MemoryChannel::MemoryChannel()
:Channel()
{
	MemoryBlock::set(&m_head, 0, sizeof(m_head));
}

MemoryChannel::~MemoryChannel(){

}

MemoryChannel::Result MemoryChannel::setMessageSize(Size size){
	if (size < sizeof(RingHead) || size > (PAGESIZE / 2))
	{
		return InvalidArgument;
	}
	m_messageSize = size;
	m_maximumMessages = (PAGESIZE / m_messageSize) - 1;

	return Success;
}

MemoryChannel::Result MemoryChannel::setVirtual(Address data, Address feedback){
	m_data.setBase(data);
	m_feedback.setBase(feedback);
	return Success;
}

MemoryChannel::Result MemoryChannel::setPhysical(Address data, Address feedback){
	if (m_data.map(data, PAGESIZE) != IO::Success)
	{
		return IOError;
	}
	if (m_feedback.map(feedback, PAGESIZE) != IO::Success)
	{
		return IOError;
	}
	return Success;
}

MemoryChannel::Result MemoryChannel::read(void* buffer)
{
	RingHead head;
	//Read the current ring head
	m_data.read(0, sizeof(head), &head);

	//Check if a message is present
	if (head.index==m_head.index)
	{
		return NotFound;
	}

	//Read one message
	m_data.read((m_head.index + 1)*m_messageSize, m_messageSize, buffer);
	
	//Increment head index
	m_head.index = (m_head.index + 1) % m_maximumMessages;

	//Update read index
	m_feedback.write(0, sizeof(m_head), &m_head);
	return Success;
}

//TODO: optimization for performance: write multiple messages in one shot
MemoryChannel::Result MemoryChannel::write(void *buffer){
	RingHead reader;

	//Read current ring head
	m_feedback.read(0, sizeof(RingHead), &reader);

	//Check if buffer space is available for the message
	if (((m_head.index + 1) % m_maximumMessages) == reader.index)
	{
		return ChannelFull;
	}
	//write the message
	m_data.write((m_head.index + 1) * m_messageSize, m_messageSize, buffer);

	//Increment write index
	m_head.index = (m_head.index + 1) % m_maximumMessages;
	m_data.write(0, sizeof(m_head), &m_head);
	return Success;
}

MemoryChannel::Result MemoryChannel::flush(){
	//Cannot flush caches in usermode. All usermode code
	//should memory map without caching.
	if (!isKernel)
	{
		return IOError;
	}

	//clean both pages from the cache
	Arch::Cache cache;
	cache.cleanData(m_data.getBase());
	cache.cleanData(m_feedback.getBase());
	return Success;
}