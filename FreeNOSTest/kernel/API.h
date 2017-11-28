#pragma once
#ifndef __SYSTEM
#error Do not include FreeNOS/API.h directly, use FreeNOS/system.h instead
#endif

#include "Log.h"
#include "Types.h"
#include "Vector.h"

//defgroup kernel kernel (generic)

//Generic kernel API implemetation.
class API
{
public:
	//Enumeration of supported generic kernel API functions.
	//Architectures or System implementations can optionally
	//introduce additional specific APIs.
	typedef enum Number
	{
		PrivExecNumber = 1,
		ProcessCtlNumber,
		SystemInfoNumber,
		VMCopyNumber,
		VMCtlNumber,
		VMShareNumber,
		IOCtlNumber
	}Number;

	//Enumeration of generic kernel API error codes.
	typedef enum Error
	{
		Success = 0,
		AccessViolation = -1,
		RangeError = -2,
		NotFound = -3,
		InvalidArgument = -4,
		OutOfMemory = -5,
		IOError = -6,
		AlreadyExists = -7
	}Error;

	//Function which handles an kernel API(system call) request.
	//return Status code of the APIHandler execution.
	typedef ::Error Handler(ulong, ulong, ulong, ulong, ulong);

	//Various actions which may be performed inside an APIHandler.
	typedef enum Operation
	{
		Create = 0,
		Delete = 1,
		Send = 2,
		Receive = 3,
		SendReceive = 4,
		Read = 5,
		Write = 6,
		ReadPhys = 7
	}Operation;

	//Constructor
	API();

	//Execute a generic API function.
	::Error invoke(Number number, 
				   ulong arg1,
				   ulong arg2,
				   ulong arg3,
				   ulong arg4,
				   ulong arg5);

private:
	//API handlers
	Vector<Handler*> m_apis;
};

//Operator to print a Operation to  a Log
Log& operator << (Log& log, API::Operation op);

//Include generic kernel API functions.

#include "API/PrivExec.h"
