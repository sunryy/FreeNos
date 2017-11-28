#pragma once

#include "System.h"

//Available operations to perform using PrivExec()
typedef enum PrivOperation
{
	Idle=0,
	Reboot = 1,
	Shutdown = 2,
	WriteConsole = 3
}PrivOperation;

//Prototype for user applications. Performs various privileged operations.
inline Error PrivExec(PrivOperation op, Address param = 0)
{
	return trapKernel2(API::PrivExecNumber, op, param);
}

/**
* Prototype for kernel handler.
*/
extern Error PrivExecHandler(PrivOperation op, Address param);
