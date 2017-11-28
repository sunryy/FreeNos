#include "spawn.h"

#include "intel/pc/System.h"
#include "ExecutableFormat.h"
#include "Types.h"
#include "Runtime.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"

int spawn(Address program, Size programSize, const char *command)
{
	ExecutableFormat *fmt;
	ExecutableFormat::Region regions[16];
	Memory::Range range;
	uint count = 0;
	pid_t pid = 0;
	Size numRegions = 16;
	Address entry;

	//Attempt to read executable format
	if (ExecutableFormat::find((u8 *)program, programSize, &fmt)!=ExecutableFormat::Success)
	{
		return -1;
	}
	//Retrieve memory regions
	if (fmt->entry(&entry) != ExecutableFormat::Success)
	{
		return -1;
	}
	if (fmt->entry(&entry) != ExecutableFormat::Success)
	{
		return -1;
	}
	//Create new process
	pid = ProcessCtl(ANY, Spawn, entry);

	//this process can read the libexec data once, and then let coreserver create a proces for it.
	//Map program regions into virtual memory of the new process
	for (Size i = 0; i < numRegions; i++)
	{
		//Copy executable memory from this region
		range.virt = regions[i].virt;
		range.phys = ZERO;
		range.size = regions[i].size;
		range.access = Memory::User |
					   Memory:Readable |
					   Memory::Writable |
					   Memory::Executable;

		//Create mapping first
		if (VMCtl(pid, Map, &range) != 0)
		{
			errno = EFAULT;
			return -1;
		}
		//Copy bytes
		VMCopy(pid, API::Write, (Address)regions[i].data,
			regions[i].virt, regions[i].size);
	}

	//Create mapping for  command-line arguments.
	range.virt = ARGV_ADDR;
	range.phys = ZERO;
	range.size = PAGESIZE;
	VMCtl(pid, Map, &range);

	//Allocate arguments
	char *arguments = new char[PAGESIZE];
	char *arg = (char *)command;
	memset(arguments, 0, PAGESIZE);

	//Fill in arguments
	while (*command && count < PAGESIZE / ARGV_SIZE)
	{
		if (*command == ' ')
		{
			strlcpy(arguments + (ARGV_SIZE * count), arg, command - arg + 1);
			count++;
			arg = (char *)(command + 1);
		}
		command++;
	}
	//The last argument
	strlcpy(arguments + (ARGV_SIZE * count), arg, command - arg + 1);

	//Copy argc/argv into the new process
	if ((VMCopy(pid, API::Write, (Address)arguments,
				(Address)ARGV_SIZE, PAGESIZE)) < 0)
	{
		delete arguments;
		errno = EFAULT;
		return -1;
	}

	//Let the child begin execution
	ProcessCtl(pid, Resume);

	//Done. Cleanup.
	delete arguments;
	return pid;
}

