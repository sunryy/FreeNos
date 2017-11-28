#pragma once
#include "Types.h"

/**Binary 1 means true.*/
#define  TRUE	1

/**Binary zero means false.*/
#define FALSE	0

#ifndef NULL
#define NULL (void*)0
#endif

#define ZERO	0
#define QUOTE(x)	\
	#x
/** Indirect the  given input.*/
#define IQUOTE(x)	\
	QUOTE(x)

#define kiloByte(v) ((v)*1024)
#define MegaByte(v)	((v)*1024*1024)
#define GigaByte(v) ((v) * 1024 * 1024 * 1024)

//TODO: #warning Integer range depends on the architecture. Move to libarch.
/**Minimum value of an object of type long int.*/
#define LONG_MIN -2147483647L

/**Maximum value of an object of type long int.*/
#define LONG_MAX 2147483647L
#define ULONG_MIN 0LU

#define ULONG_MAX 4294967295LU

#define INT_MIN -2147483647

#define INT_MAX 214748364

#define UINT_MIN 0U

#define UINT_MAX 494967295U

/**
*	Calculate a division, and round to up any remainning.
*	@param number Input number.
*	@param divisor Divisor number.
*	@return Ceiled number.
*/
#define CEIL(number, divisor)	\
	((number) % (divisor) ?		\
	((number) / (divisor)) + 1 : (number) / (divisor))

#ifdef __cplusplus

/**
*	Absolute value of a double.
*/
inline double doubleAbsolute(double number)
{
	return number < 0 ? -number : number;
}

/**
*	Compare two doubles using a epsilon number as precision indicator.
*/
inline bool doubleEquals(double a, double b, double epsilon)
{
	return doubleAbsolute(a - b) < epsilon;
}

#endif /* __cplusplus*/

/** Caculates ofsets in data structures.*/
#define offsetof(TYPE, MEMBER)	\
	((Size)& ((TYPE *)0)->MEMBER)

/**Used to define external C functions.*/
#ifdef __cplusplus
#define C "C"
#define CPP
#else
#define C
#endif	/* c_plusplus */

/**
*	Can be used to link a symbol inside a specific section.
*	@param s Section name.
*/
#define SECTION(s)	\
	__attrubute__((__section_(s)))

/**
*	Declares an symbol to be forcibly "userd".
*/

#define USED	\
	__attribute__((__used__))

/**
*	Ensures strict minimum memory reuquirements.
*	This option effectively disabled extra padding by the compiler.
*/
#define PACKED	\
	__attribute__((__packed__))

/**
*	Aligns a symbol at the given boundary.
*	@param n Boundary to align.
*/
#define ALIGN(n)	\
	__attribute__((aligned(n)))

