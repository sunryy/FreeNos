#pragma once
#ifndef __ASSEMBLER__

/**
*@defgroup types types
*@{
*/

/**
*Restrict bit operatios.
*@see http:/kernaltrap.org/node/3848
*/
#if 0
#define BITWISE \
	__attribute__((bitwise))
#else
#define BITWISE
#endif

/**
*@name Unsigned integers.
*@{
*/

/**Unsigned integer number.*/
typedef unsigned int uint;

typedef unsigned long ulong;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

/**
*	@}
*/

/**
*	@name Signed integers.
*	@{
*/

/**Signed integer number.*/
typedef signed int sint;
typedef signed long slong;
typedef signed long long s64;
typedef signed int s32;
typedef signed short int s16;
typedef signed char s8;

/**
*	@}
*/

/**
*	@name Bitwise checked integers.
*	@see http://kerneltrap.org/node/3848
*	@{
*/


/** Unsigned 64-bit little endian number. */
typedef u64 BITWISE le64;

/** Unsigned 64-bit big endian number. */
typedef u64 BITWISE be64;

/** Unsigned 32-bit little endian number. */
typedef u32 BITWISE le32;

/** Unsigned 32-bit big endian number. */
typedef u32 BITWISE be32;

/** Unsigned 16-bit little endian number. */
typedef u16 BITWISE le16;

/** Unsigned 16-bit big endian number. */
typedef u16 BITWISE be16;

/** Unsigned 8-bit little endian number. */
typedef u8  BITWISE le8;

/** Unsigned 8-bit big endian number. */
typedef u8  BITWISE be8;

/**
* @}
*/

/** Any sane size indicator cannot go negative. */
typedef unsigned int Size;

/** A memory address. */
typedef unsigned long Address;

/** User Identity. */
typedef unsigned short UserID;

/** Group Identity. */
typedef unsigned short GroupID;

/** Process Identification Number. */
typedef u16 ProcessID;

/**
* Describes a device ID number.
*/
typedef struct DeviceID
{
	/** Major device ID number is a PID. */
	ProcessID major;

	/** Device specific minor ID number. */
	u16 minor;
}
DeviceID;

/**
* Error code defined in Error.h
* @see Error.h
*/
typedef slong Error;

#ifdef __cplusplus

namespace Number
{
	/**
	* Numeral system base type.
	*/
	typedef enum Base
	{
		Dec, /** Decimal: 0-10 */
		Hex, /** Hexadecimal: 0x0-0xf */
	}
	Base;
};

#endif /* __cplusplus */

/**
* @}
*/

#endif /* __ASSEMBLER__ */