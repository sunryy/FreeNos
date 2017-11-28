#pragma once
//Basic message format for sending on a Channel
class ChannelMessage
{
public:
	//Message types
	enum Type
	{
		Request = 0;
		Response = 1;
	};

	//Message type is either a request or response
	Type type : 1;
	//Optional request identifier
	Size identifier : 31;
};