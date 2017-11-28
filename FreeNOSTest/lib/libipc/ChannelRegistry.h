#pragma once
#include "HashTable.h"
#include "Types.h"

class Channel;
//Registration for Channels.
class ChannelRegistry{
public:
	//Result codes.
	enum Result
	{
		Success,
		InvalidArgument,
		InvalidSize,
		IOError,
		NotFound
	};

	/**
	* Constructor.
	*/
	ChannelRegistry();

	/**
	* Destructor
	*/
	virtual ~ChannelRegistry();

	/**
	* Get one consumer.
	*
	* @param pid ProcessID of the channel to get
	* @return Channel pointer if found or ZERO
	*/
	Channel * getConsumer(ProcessID pid);

	/**
	* Get one producer.
	*
	* @param pid ProcessID of the channel to get
	* @return Channel pointer if found or ZERO
	*/
	Channel * getProducer(ProcessID pid);

	/**
	* Get all consumers
	*
	* @return HashTable with consumer channels
	*/
	HashTable<ProcessID, Channel *> & getConsumers();

	/**
	* Get all producers
	*
	* @return HashTable with all producer channels
	*/
	HashTable<ProcessID, Channel *> & getProducers();

	/**
	* Register consumer channel.
	*
	* @param pid ProcessID of the attached process
	* @param channel Channel object
	* @return Result code
	*/
	Result registerConsumer(ProcessID pid, Channel *channel);

	/**
	* Register producer channel.
	*
	* @param pid ProcessID of the attached process
	* @param channel Channel object
	* @return Result code
	*/
	Result registerProducer(ProcessID pid, Channel *channel);

	/**
	* Unregister consumer channel.
	*
	* @param pid ProcessID of the attached process
	* @return Result code
	*/
	Result unregisterConsumer(ProcessID pid);

	/**
	* Unregister producer channel.
	*
	* @param pid ProcessID of the attached process
	* @return Result code
	*/
	Result unregisterProducer(ProcessID pid);

private:
	//Contains registered consumer channels
	HashTable<ProcessID, Channel *> m_consumer;

	//Contains registered producer channels
	HashTable<ProcessID, Channel *> m_producer;

};