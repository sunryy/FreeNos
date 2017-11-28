#pragma once
#include "stdarg.h"

#include "sys/types.h"
#include "Macros.h"

//Seek operation

//Seek relative to  current position.
#define SEEK_CUR	0

//Seek relative to end-of-file
#define SEEK_END	1

//Seek relativ to start-of-file.
#define SEEK_SET	2

//File streams

//A structure containing information about a file.
typedef struct FILE
{
	//File descriptor.
	int fd;
};

//Open a stream.
extern C FILE* fopen(const char *filename, const char *mode);

//Binary input.
extern C size_t fread(void *ptr, size_t size, 
					  size_t nitems, FILE *stream);

/**
* @brief Close a stream.
*
* The fclose() function shall cause the stream pointed to by stream
* to be flushed and the associated file to be closed. Any unwritten
* buffered data for the stream shall be written to the file; any unread
* buffered data shall be discarded. Whether or not the call succeeds, the
* stream shall be disassociated from the file and any buffer set by the setbuf()
* or setvbuf() function shall be disassociated from the stream. If the associated
* buffer was automatically allocated, it shall be deallocated.
*
* @param stream File stream to close.
* @return Upon successful completion, fclose() shall return 0; otherwise,
*         it shall return EOF and set errno to indicate the error.
*/
extern C int fclose(FILE *stream);

/**
	* @}
	*/

//Output a debug message using printf().
#define dprintf(fmt, ...)	\
	printf("{%s:%d}:" fmt, __FILE__, __LINE__, ##__VA_ARGS__);

//Write a formatted string into a buffer.
extern C int snprintf(char *buffer, unsigned int size, const char *fmt, ...);

//Write a formatted string into a buffer.
extern C int vsnprintf(char *buffer, unsigned int size, const char *fmt, va_list args);

/**
* Output a formatted string to standard output.
* @param format Formatted string.
* @param ... Argument list.
* @return Number of bytes written or error code on failure.
*/
extern C int printf(const char *format, ...);

/**
* Output a formatted string to standard output, using a variable argument list.
* @param format Formatted string.
* @param ... Argument list.
* @return Number of bytes written or error code on failure.
*/
extern C int vprintf(const char *format, va_list args);

