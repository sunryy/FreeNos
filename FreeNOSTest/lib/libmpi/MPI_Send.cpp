#include "intel/pc/System.h"
#include "Index.h"
#include "MemoryChannel.h"
#include "mpi.h"
#include "MPIMessage.h"

extern Index<MemoryChannel> *writeChannel;
int MPI_Send(const void *buf,
	int count,
	MPI_Datatype datatype,
	int dest,
	int tag,
	MPI_Comm comm)
{
	MPIMessage msg;
	MemoryChannel *ch;

	if (datatype != MPI_INT)
	{
		return MPI_ERR_UNSUPPORTED_DATAREP;
	}
	if (!(ch = (MemoryChannel *)writeChannel->get(dest)))
	{
		return MPI_ERR_RANK;
	}
	for (int i = 0; i < count; i++)
	{
		msg.integer = *(((int *)buf) + i);
		//TODO: replace with Channellient::syncSendTo
		while (ch->write(&msg) != Channel::Success)
		{
			;
		}
	}
	return MPI_SUCCESS;
}