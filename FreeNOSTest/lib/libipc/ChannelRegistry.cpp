#include "ChannelRegistry.h"
#include "Channel.h"


ChannelRegistry::ChannelRegistry()
{
}

ChannelRegistry::~ChannelRegistry()
{
}

Channel *ChannelRegistry::getConsumer(ProcessID pid){
	const Channel * const *ch = m_consumer.get(pid);
	if (ch)
	{
		return (Channel *)*ch;
	}
	else
	{
		return ZERO;
	}
}

Channel * ChannelRegistry::getProducer(ProcessID pid)
{
	const Channel * const *ch = m_producer.get(pid);
	if (ch)
		return (Channel *)*ch;
	else
		return ZERO;
}

HashTable<ProcessID, Channel *> & ChannelRegistry::getConsumers()
{
	return m_consumer;
}

HashTable<ProcessID, Channel *> & ChannelRegistry::getProducers()
{
	return m_producer;
}

ChannelRegistry::Result ChannelRegistry::registerConsumer(
	ProcessID pid,
	Channel *channel)
{
	m_consumer.insert(pid, channel);
	return Success;
}

ChannelRegistry::Result ChannelRegistry::registerProducer(
	ProcessID pid,
	Channel *channel)
{
	m_producer.insert(pid, channel);
	return Success;
}

ChannelRegistry::Result ChannelRegistry::unregisterConsumer(ProcessID pid)
{
	Channel *ch = getConsumer(pid);
	if (ch)
		delete ch;

	if (m_consumer.remove(pid) > 0)
		return Success;
	else
		return NotFound;
}

ChannelRegistry::Result ChannelRegistry::unregisterProducer(ProcessID pid)
{
	Channel *ch = getProducer(pid);
	if (ch)
		delete ch;

	if (m_producer.remove(pid) > 0)
		return Success;
	else
		return NotFound;
}
