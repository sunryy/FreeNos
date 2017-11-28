#include "forkexec.h"

#include "intel/pc/System.h"
#include "ExecutableFormat.h"
#include "FileSystemMessage.h"
#include "Types.h"
#include "Runtime.h"
#include "string.h"
#include "sys/stat.h"
#include "errno.h"
#include "fcntl.h"
#include "unistd.h"

int forkexec(const char *path, const char *argv[]){
	FileSystemMessage msg;
	ExecutableFormat *fmt;
	ExecutableFormat::Region regions[16];
	Memory::Range range;
	uint count = 0;
	pid_t pid = 0;
	Size numRegions = 16;
	int fd;
	Vector<FileDescriptor> *fds = getFiles();
	struct stat st;
	u8 *image;
	Address entry;

	//Read the program image
	if (stat(path, &st) != 0)
	{
		return -1;
	}
	if ((fd=open(path, O_RDONLY)) < 0)
	{
		return -1;
	}
	image = new u8[st.st_size];
	if ( read(fd, image, st.st_size) != st.st_size)
	{
		delete image;
		return -1;
	}
	close(fd);

	//Attempt to read executable format
	if (ExecutableFormat::find(image, st.st_size, &fmt) != ExecutableFormat::Success)
	{
		return -1;
	}

	//Retrieve memory regions
	if (fmt->regions(regions, &numRegions) != ExecutableFormat::Success)
	{
		return -1;
	}

	if (fmt->entry(&entry) != ExecutableFormat::Success)
	{
		return -1;
	}

	//Create new process
	pid = ProcessCtl(ANY, Spawn, entry);

	//TODO: check the result of ProcessCtl()
	//Map program regions into virtual memory of the new process
	for (Size i = 0; i < numRegions; i++)
	{
		//Copy executable memory from this region
		range.virt = regions[i].virt;
		range.phys = ZERO;
		range.size = regions[i].size;
		range.access = Memory::User |
			Memory::Readable |
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
	//Create mapping for command-line arguments.
	range.virt = ARGV_ADDR;
	range.phys = ZERO;
	range.size = PAGESIZE;
	VMCtl(pid, Map, &range);

	//Allocate arguments
	char *arguments = new char[PAGESIZE];
	memset(arguments, 0, PAGESIZE);

	//Fill in arguments
	while (argv[count] && count < PAGESIZE / ARGV_SIZE)
	{
		strlcpy(arguments + (ARGV_SIZE * count), argv[count], ARGV_SIZE);
		count++;
	}

	//Copy argc/argv into the new process
	if ((VMCopy(pid, API::Write, (Address)arguments,
		 (Address)ARGV_ADDR, PAGESIZE)) < 0)
	{
		delete arguments;
		errno = EFAULT;
		return -1;
	}
	//Let the Child begin execution
	ProcessCtl(pid, Resume);

	//Send a pointer to our list of file descriptors to the child
	msg.from = SELF;
	msg.filetype = ChannelMessage::Request;
	msg.path = (char *)fds->vector();
	ChannelClient::instance->syncSendReceive(&msg, pid);

	//Done.Cleanup.
	delete arguments;
	return pid;
}

