#include "intel/pc/System.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "unistd.h"

int main(int argc, char **argv)
{
	u64 t1 = 0, t2 = 0;
	ProcessInfo info;
	Memory::Range range;
	char *foo[128];

	t1 = timestamp();
	ProcessCtl(SELF, GetPID);
	t2 = timestamp();

	printf("SystemCall (GetPID) Ticks: %u\r\n", t2 - t1);
	t1 = timestamp();
	ProcessCtl(SELF, InfoPID, (Address)&info);
	t2 = timestamp();

	printf("SystemCall (InfoPID) Ticks:%u\r\n", t2 - t1);

	t1 = timestamp();
	ProcessCtl(SELF, Schedule);
	t2 = timestamp();

	printf("SystemCall (InfoPID) Ticks:%u\r\n", t2 - t1);
	range.virt = 0x80000000;
	range.size = PAGESIZE;

	t1 = timestamp();
	ProcessCtl(SELF, LookupVirtual, &range);
	t2 = timestamp();

	printf("SystemCall (VMCtl)Ticks:%u\r\n", t2 - t1);
	t1 = timestamp();
	getpid();
	t2 = timestamp();

	printf("IPC Ticks:%u\r\n", t2 - t1);

	t1 = timestamp();
	for (int i = 0; i < 128; i++)
	{
		delete foo[i];
	}
	t2 = timestamp();
	printf("release() Ticks: %u (%u AVG)\r\n", (u32)(t2 - t1), (u32)(t2 - t1) / 128);
	//Done.
	return EXIT_SUCCESS;
}