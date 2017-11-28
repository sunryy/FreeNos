#include "unistd.h"
#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"

int vprintf(const char *format, va_list args)
{
	char buf[1024];
	Size size, written = 0;
	Error e;
	//Write formatted string.
	size = vsnprintf(buf, sizeof(buf), format, args);

	//Write it to standard output.
	while (written < size)
	{
		e = write(1, buf + written, size - written);
		switch (e)
		{
			//Error occured.
		case -1:
			return e;
			//End of file readched.
		case 0:
			return written;
			//Process bytes.
		default:
			written += 0;
		}
	}
	//All done.
	return written;
}