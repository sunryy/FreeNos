#include "ChannelClient.h"

#include "intel/pc/System.h"
#include "HashIterator.h"

#include "FileSystemMessage.h"
#include "MemoryChannel.h"

ChannelClient::ChannelClient()
: Singleton<ChannelClient>(this)
{
	m_registry = 0;
}

ChannelClient::~ChannelClient()
{
}

ChannelRegistry * ChannelClient::getRegistry()
{
	return m_registry;
}

ChannelClient::Result ChannelClient::setRegistry(ChannelRegistry *registry)
{
	m_registry = registry;
	return Success;
}

ChannelClient::Result ChannelClient::initialize()
{
	return Success;
}

ChannelClient::Result ChannelClient::connect(ProcessID pid){
	Address prodAddr, consAddr;
	SystemInformation info;

	//Allocate consumer
	MemoryChannel *cons = new MemoryChannel;
	if (!cons)
	{
		return OutOfMemory;
	}

	cons->setMessageSize(sizeof(FileSystemMessage));
	cons->setMode(Channel::Consumer);

	//Allocate producer
	MemoryChannel *prod = new MemoryChannel;
	if (!prod)
	{
		delete cons;
		return OutOfMemory;
	}
	prod->setMessageSize(sizeof(FileSystemMessage));
	prod->setMode(Channel::Producer);

	//Call VMShare to create memory mapping for MemoryChannel.
	ProcessShares::MemoryShare share;
	share.pid = pid;
	share.coreId = info.coreId;
	share.tagId = 0;
	share.range.size = PAGESIZE * 4;
	share.range.virt = 0;
	share.range.phys = 0;
	share.range.access = Memory::User | Memory::Readable | Memory::Writable;

	//Create shared memory mapping
	Error r = VMShare(pid, API::Create, &share);
	switch (r)
	{
	case API::Success:
	{
						 prodAddr = share.range.virt;
						 consAddr = share.range.virt + (PAGESIZE * 2);
						 break;
	}
	case API::AlreadyExists:
	{
							   prodAddr = share.range.virt + (PAGESIZE * 2);
							   consAddr = share.range.virt;
							   break;
	}
	default:
	{
			   return IOError;
	}
	}
	
	//Setup producer memory address
	if (prod->setVirtual(prodAddr, prodAddr + PAGESIZE)!=MemoryChannel::Success)
	{
		delete prod;
		delete cons;
		return IOError;
	}
	// Setup consumer memory address
	if (cons->setVirtual(consAddr, consAddr + PAGESIZE) != MemoryChannel::Success)
	{
		delete prod;
		delete cons;
		return IOError;
	}

	// Register channels
	m_registry->registerConsumer(pid, cons);
	m_registry->registerProducer(pid, prod);
	return Success;
}

ChannelClient::Result ChannelClient::receiveAny(void *buffer, ProcessID *pid)
{
	for (HashIterator<ProcessID, Channel *> i(m_registry->getConsumers()); i.hasCurrent(); i++)
	{
		if (i.current()->read(buffer) == Channel::Success)
		{
			*pid = i.key();
			return Success;
		}
	}
	return NotFound;
}

ChannelClient::Result ChannelClient::sendRequest(ProcessID pid,
	void *buffer,
	CallbackFunction *callback)
{
	Request *req = 0;
	Size identifier = 0;
	Channel *ch = findProducer(pid);
	if (!ch)
		return NotFound;

	// Find request object
	for (Size i = 0; i < m_requests.count(); i++)
	{
		req = (Request *)m_requests.get(i);
		if (!req->active)
		{
			identifier = i;
			break;
		}
	}
	// Allocate new request object if none available
	if (!req || req->active)
	{
		req = new Request;
		req->message = new FileSystemMessage;
		identifier = m_requests.insert(*req);
	}
	// Fill request object
	MemoryBlock::copy(req->message, buffer, ch->getMessageSize());
	req->pid = pid;
	req->message->identifier = identifier;
	req->message->type = ChannelMessage::Request;
	req->callback = callback;
	req->active = true;

	DEBUG("sending request with id = " << req->message->identifier << " to PID " << pid);

	// Try to send the message
	if (ch->write(req->message) != Channel::Success)
	{
		req->active = false;
		return IOError;
	}
	// Wakeup the receiver
	ProcessCtl(pid, Resume, 0);
	return Success;
}

ChannelClient::Result ChannelClient::processResponse(ProcessID pid,
	ChannelMessage *msg)
{
	Size count = m_requests.count();

	for (Size i = 0; i < count; i++)
	{
		Request *req = (Request *)m_requests.get(i);

		if (req->active &&
			req->pid == pid &&
			req->message->identifier == msg->identifier)
		{
			req->callback->execute(msg);
			req->active = false;
			return Success;
		}
	}
	return NotFound;
}


Channel * ChannelClient::findConsumer(ProcessID pid)
{
	Result r;
	Channel *ch = m_registry->getConsumer(pid);
	if (ch)
		return ch;

	// Try to connect
	if ((r = connect(pid)) != Success)
		return ZERO;

	return m_registry->getConsumer(pid);
}

Channel * ChannelClient::findProducer(ProcessID pid)
{
	Result r;
	Channel *ch = m_registry->getProducer(pid);
	if (ch)
		return ch;

	// Try to connect
	if ((r = connect(pid)) != Success)
		return ZERO;

	return m_registry->getProducer(pid);
}

ChannelClient::Result ChannelClient::syncReceiveFrom(void *buffer, ProcessID pid)
{
	Channel *ch = findConsumer(pid);
	if (!ch)
		return NotFound;

	// TODO: for inter-core communication, the wakeup call becomes an IPI!
	while (ch->read(buffer) != Channel::Success)
		ProcessCtl(SELF, EnterSleep, 0);

	return Success;
}

ChannelClient::Result ChannelClient::syncSendTo(void *buffer, ProcessID pid)
{
	Channel *ch = findProducer(pid);
	if (!ch)
		return NotFound;

	while (true)
	{
		switch (ch->write(buffer))
		{
		case Channel::Success:
			ProcessCtl(pid, Resume, 0);
			return Success;

		case Channel::ChannelFull:
			ProcessCtl(pid, Resume, 0);
			break;

		default:
			return IOError;
		}
		ProcessCtl(SELF, Schedule, 0);
	}
	return IOError;
}

ChannelClient::Result ChannelClient::syncSendReceive(void *buffer, ProcessID pid)
{
	Result r = syncSendTo(buffer, pid);
	if (r != Success)
		return r;

	return syncReceiveFrom(buffer, pid);
}
