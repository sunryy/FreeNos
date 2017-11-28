#pragma once
#if defined(__ASSERT__)&&!defined(__HOST__)

#include "Macros.h"
#include "Types.h"

#ifdef __SERVER__
#include <LogMessage.h>
#include <stdlib.h>
#endif

/**
*@brief Runtime functions
*@{
*/

/**
*Function which prints a message, and then terminates itself.
*@param fmt Formatted message.
*@param ... Argument list.
*/
extern C void __assertFailure(const char *fmt, ...);

/**
*Verify that the given address is readable.
*@param addr Address to verify.
*/
extern C int __assertRead(Address addr);


/**
* Verify that the given address is writeable.
* @param addr Address to verify.
*/
extern C int __assertWrite(Address addr);

/**
* @}
*/

/**
* @brief Preprocessor macros
* @{
*/

/**
* Invokes __assertFailure for applications, and log() + exit() for servers.
* @param fmt Formatted string.
* @param ... Argument list.
* @return Never.
*/
#ifdef __SERVER__
#define raiseFailure(fmt, ...) \
	log(fmt, ##__VA_ARGS__); \
	exit(1);
#else
#define raiseFailure(fmt, ...) \
	__assertFailure(fmt, ##__VA_ARGS__);
#endif

/**
* Verify that a given expression evaluates to true.
* @param exp Boolean expression.
*/
#define assert(exp) \
if (!(exp)) \
{ \
	raiseFailure("[%s:%d]: *** Assertion `%s' failed ***\n", \
	__FILE__, __LINE__, #exp); \
}

/**
* Presume that the given address is readable.
* @param addr Address to check.
*/
#define assertRead(addr) \
	assert(__assertRead((Address)addr))

/**
* Presume that the given address is writeable.
* @param addr Address to check.
*/
#define assertWrite(addr) \
	assert(__assertWrite((Address)addr))

/**
* @}
*/

#else

/**
* @brief Dummy preprocessor macros
* @{
*/

/**
* Dummy assertion function which does not perform any check.
* @param exp Expression is ignored.
*/
#define assert(exp)

/**
* Dummy assertion function for checking read access on an address.
* @param addr Address is ignored.
*/
#define assertRead(addr)

/**
* Dummy assertion function for checking read access on an address.
* @param addr Address is ignored.
*/
#define assertWrite(addr)

/**
* @}
*/
