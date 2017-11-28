#include "intel/pc/System.h"
#include "Index.h"
#include "MemoryChannel.h"
#include "mpi.h"
#include "MPIMessage.h"

extern Index<MemoryChannel> *readChannel;

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
{
	MPIMessage msg;
	MemoryChannel *ch;
	if (datatype != MPI_INT)
	{
		return MPI_ERR_UNSUPPORTED_DATAREP;
	}
	if (!(ch=(MemoryChannel *)readChannel->get(source)))
	{
		return MPI_ERR_RANK;
	}
	for (int i = 0; i < count; i++)
	{
		//TODO:replace with ChannelClient::syncReceiveFrom
		while (ch->read(&msg) != Channel:Success)
		{
			;
		}
		*(((int *)buf) + i) = msg.integer;
	}
	return MPI_SUCCESS;
}