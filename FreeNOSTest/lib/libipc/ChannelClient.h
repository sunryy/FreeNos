#pragma once
#include "Singleton.h"
#include "Callback.h"
#include "Index.h"
#include "ChannelRegistry.h"
#include "Channel.h"
#include "ChannelMessage.h"

//Client for using Channels.
class ChannelClient : public Singleton<ChannelClient>
{
private:
	//Holds an outgoing request
	typedef struct Request{
		bool active;
		ProcessID pid;
		ChannelMessage *message;
		CallbackFunction *callback;

		const bool operator==(const struct Request &req)const {
			return req.message == message && req.callback == callback;
		}

		const bool operator !=(const struct Request &req) const{
			return req.message != message || req.callback != callback;
		}
	}
	Requst;

public:
	//Result codes.
	enum Result
	{
		Success,
		InvalidArgument,
		InvalidSize,
		IOError,
		OutOfMemory,
		NotFound
	};

	/**
	* Constructor.
	*/
	ChannelClient();

	/**
	* Destructor
	*/
	virtual ~ChannelClient();

	/**
	* Get channel registry.
	*
	* @return ChannelRegistry object pointer or ZERO if not set
	*/
	ChannelRegistry * getRegistry();

	/**
	* Assign channel registry.
	*
	* @param registry ChannelRegistry object pointer
	* @return Result code
	*/
	Result setRegistry(ChannelRegistry *registry);

	/**
	* Initialize the ChannelClient.
	*
	* @return Result code
	*/
	virtual Result initialize();

	/**
	* Connect to a process.
	*
	* This function creates a producer and consumer Channel
	* to the given process and registers it with the ChannelRegistry.
	*
	* @param pid ProcessID for the process to connect to.
	* @return Result code
	*/
	virtual Result connect(ProcessID pid);

	/**
	* Try to receive message from any channel.
	*
	* @param buffer Message buffer for output
	* @param pid ProcessID for output
	* @return Result code
	*/
	virtual Result receiveAny(void *buffer, ProcessID *pid);

	/**
	* Send asynchronous request message
	*
	* The client assigns an internal request identifier
	* for the message and ensures that the callback will be
	* called when a response messages is received.
	*
	* @param pid ProcessID to send the message to
	* @param
	*/
	virtual Result sendRequest(ProcessID pid,
		void *buffer,
		CallbackFunction *callback);

	/**
	* Process a response message
	*
	* @param pid ProcessID from which we receive the message
	* @param msg Message which is received
	*/
	virtual Result processResponse(ProcessID pid,
		ChannelMessage *msg);

	/**
	* Synchronous receive from one process.
	*
	* @param buffer Message buffer for output
	* @param pid ProcessID for the channel
	* @return Result code
	*/
	virtual Result syncReceiveFrom(void *buffer, ProcessID pid);

	/**
	* Synchronous send to one process.
	*
	* @param buffer Message buffer to send
	* @param pid ProcessID for the channel
	* @return Result code
	*/
	virtual Result syncSendTo(void *buffer, ProcessID pid);

	/**
	* Synchronous send and receive to/from one process.
	*
	* @param buffer Message buffer to send/receive
	* @param pid ProcessID for the channel
	* @return Result code
	*/
	virtual Result syncSendReceive(void *buffer, ProcessID pid);

	private:
		//Get consumer for a process.
		Channel *findConsumer(ProcessID pid);

		//Get producer for a process.
		Channel *findProducer(ProcessID pid);

		//Contains registered channels.
		ChannelRegistry *m_registry;

		//Contains ongoing requests.
		Index<Request> m_requests;

};

