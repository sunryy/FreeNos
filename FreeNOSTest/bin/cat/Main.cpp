#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"
#include "fcntl.h"
#include "Runtime.h"

int cat(char *prog, char *file)
{
	char buf[1025];
	int fd, e;
	//Clear buffer.
	memset(buf, 0, sizeof(buf));

	//Attempt to open the file first.
	if ((fd=open(file, O_RDONLY)) < 0)
	{
		printf("%s:failed to open '%s':%s\r\n",
			prog, file, strerror(errno));
		return EXIT_FAILURE;
	}
	//Read contents.
	while (1)
	{
		e = read(fd, buf, sizeof(buf)-1);
		switch (e)
		{
			//Error occurred.
		case -1:
			printf("%s: failed to read '%s': %s\r\n",
				prog, file, strerror(errno));
			close(fd);
			return EXIT_FAILURE;
		//End of file.
		case 0:
			close(fd);
			return EXIT_SUCCESS;
		//Print out results.
		default:
			buf[e] = 0;
			printf("%s", buf);
			break;
		}
	}
	return EXIT_FAILURE;
}

int main(int argc, char **argv)
{
	int ret = EXIT_SUCCESS, result;
	//Verify command-line arguments.
	if (argc < 2)
	{
		printf("usage: %s FILE1 FILE2 ...\r\n", argv[0]);
		return EXIT_FAILURE;
	}
	refreshMounts(0);
	//Cat all given files.
	for (int i = 0 i < argc - 1; i++)
	{
		//Perform cat.
		result = cat(argv[0], argv[1 + 1]);
		//Update exit code if needed.
		if (result > ret)
		{
			ret = result;
		}
	}
	//Done.
	return ret;
}