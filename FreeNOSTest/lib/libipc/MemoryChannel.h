#pragma once
#include "intel/pc/System.h"
#include "Types.h"
#include "Channel.h"

 //Unidirectional point-to-point channel using shared memory.
class MemoryChannel :public Channel
{
private:

	typedef struct RingHead 
	{
		//Index where the ring buffer starts.
		Size index;
	}
	RingHead;

public:


	/**
	* Constructor
	*/
	MemoryChannel();

	/**
	* Destructor.
	*/
	virtual ~MemoryChannel();

	/**
	* Set memory pages by virtual address.
	*
	* This function assumes that the given virtual addresses
	* are already mapped into the associated address space.
	*
	* @param data Virtual memory address of the data page.
	*             Read/Write for the producer, Read-only for the consumer.
	* @param feedback Virtual memory address of the feedback page.
	*        Read/write for the consumer, read-only for the producer.
	* @return Result code.
	*/
	Result setVirtual(Address data, Address feedback);

	/**
	* Set memory pages by physical address.
	*
	* This function maps the given physical addresses
	* into the current address space using IO::map.
	*
	* @param data Physical memory address of the data page.
	*             Read/Write for the producer, Read-only for the consumer.
	* @param feedback Physical memory address of the feedback page.
	*        Read/write for the consumer, read-only for the producer.
	* @return Result code.
	*/
	Result setPhysical(Address data, Address feedback);

	/**
	* Set message size.
	*
	* @param size New message size.
	* @return Result code.
	*/
	virtual Result setMessageSize(Size size);

	/**
	* Read a message.
	*
	* @param buffer Output buffer for the message.
	* @return Result code.
	*/
	virtual Result read(void *buffer);

	/**
	* Write a message.
	*
	* @param buffer Input buffer for the message.
	* @return Result code.
	*/
	virtual Result write(void *buffer);

	/**
	* Flush message buffers.
	*
	* Ensures that all messages are written through caches.
	*
	* @return Result code.
	*/
	virtual Result flush();

	bool operator == (const MemoryChannel & ch) const
	{
		return false;
	}

	bool operator != (const MemoryChannel & ch) const
	{
		return false;
	}

private:
	//The data page.
	Arch::IO m_data;

	//The feedback page.
	Arch::IO m_feedback;

	//Local RingHead.
	RingHead m_head;
};