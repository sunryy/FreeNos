#pragma once

//Unidirectional point-to-point messaging channel.
class Channel
{
public:
	//Result codes.
	enum Result
	{
		Success,
		InvalidArgument,
		InvalidMode,
		InvalidSize,
		IOError,
		ChannelFull,
		NotFound
	};

	//Channel modes.
	enum Mode
	{
		Producer,
		Consumer
	};

	//Constructor.
	Channel();

	//Destructor.
	virtual ~Channel();

	//Get message size
	const Size getMessageSize() const;

	//Get maximum message count.
	const Size getMaximumMessages() const;


	/**
	* Set mode.
	*
	* @param mode Channel mode.
	* @return Result code.
	*/
	Result setMode(Mode mode);

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
	virtual Result read(void *buffer) = 0;

	/**
	* Write a message.
	*
	* @param buffer Input buffer for the message.
	* @return Result code.
	*/
	virtual Result write(void *buffer) = 0;

	/**
	* Flush message buffers.
	*
	* Ensures that all messages are written through caches.
	*
	* @return Result code.
	*/
	virtual Result flush() = 0;

protected:
	//Channel mode.
	Mode m_mode;

	//Message size.
	Size m_messageSize;

	//Maximum number of message that the Channel can hold.
	Size m_maximumMessages;
};