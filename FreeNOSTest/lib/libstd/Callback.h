#pragma once
#include "Types.h"
class CallbackFunction
{
public:
	virtual void execute(void *parameter) = 0;
};

//Abstraction for providing a callback function to a object instance.
template <class Base, class ParamType> class Callback : public CallbackFunction
{
private:
	//Callback function prototype
	typedef void(Base::*Function)(ParamType *param);

public:

	//Ctr
	Callback(Base *object, Function func)
	{
		m_object = object;
		m_function = func;
	}

	virtual void execute(void *parameter)
	{
		executeOnObject((ParamType *)parameter);
	}

private:
	//Execute the callback.
	virtual void executeOnObject(ParamType *parameter)
	{
		(m_object->*m_function)(parameter);
	}

	//Object instance.
	Base *m_object;

	//Function pointer
	Function m_function;
};