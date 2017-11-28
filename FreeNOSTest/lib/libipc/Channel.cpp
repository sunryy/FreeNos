#include "Channel.h"



Channel::Channel()
{
	m_mode = Consumer;
	m_messageSize = 0;
	m_maximumMessages = 0;
}

Channel::~Channel()
{
}

const Size Channel::getMessageSize() const
{
	return m_messageSize;
}

const Size Channel::getMaximumMessages() const
{
	return m_maximumMessages;
}

Channel::Result Channel::setMode(Channel::Mode mode)
{
	m_mode = mode;
	return Success;
}

Channel::Result Channel::setMessageSize(Size size)
{
	m_messageSize = size;
	return Success;
}
