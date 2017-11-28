#include "intel/pc/System.h"
#include "mpi.h"

extern Size coreCount;
int MPI_Comm_rank(MPI_Comm comm, int *rank)
{
	SystemInformation info;
	*rank = info.coreId;
	return MPI_SUCCESS;
}

int MPI_Comm_size(MPI_Comm comm, int *size)
{
	*size = coreCount;
	return MPI_SUCCESS;
}