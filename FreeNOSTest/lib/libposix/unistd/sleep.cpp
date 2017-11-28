#include "unistd.h"
unsigned int sleep(unsigned int seconds)
{
	//Temporary busy-loop implementation, which is inaccurate.
	for (unsigned int i = 0; i < seconds * 10000000; i++)
	{
		;
	}
	return 0;
}