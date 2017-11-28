#pragma once
#include "Types.h"
#include "Macros.h"
#include "List.h"
#include "MemoryMap.h"
#include "Index.h"
#include "MemoryContext.h"

class MemoryChannel;
class Process;

//Manages memory shares for a Process.
class ProcessShares
{
public:
	typedef struct MemoryShare 
	{
		//Remote process id for this share.
		ProcessID pid;

		//CoreId for the other process
		Size coreId;

		//Share tag id is defined by the application
		Size tagId;

		//Physical memory address range.
		Memory::Range range;

		//True if the share is attache (used by both processes)
		bool attached;
		bool operator == (const struct MemoryShare & sh) const
		{
			return true;
		}
		bool operator != (const struct MemoryShare & sh) const
		{
			return false;
		}
	}
	MemoryShare;

	enum Result
	{
		Success,
		InvalidArgument,
		MemoryMapError,
		OutOfMemory,
		AlreadyExists,
		NotFound
	};


	/**
	* Constructor.
	*/
	ProcessShares(ProcessID pid);

	/**
	* Destructor function.
	*/
	virtual ~ProcessShares();

	/**
	* Get process.
	*/
	const ProcessID getProcessID() const;

	/**
	* Get MemoryContext object.
	*
	* @return MemoryContext object pointer.
	*/
	MemoryContext * getMemoryContext();

	/**
	* Set MemoryContext.
	*
	* @param context MemoryContext object
	* @return Result code.
	*/
	Result setMemoryContext(MemoryContext *context);

	/**
	*
	*/
	Result createShare(ProcessShares & instance,
		MemoryShare *share);

	/**
	* Create memory share.
	*
	* @param pid ProcessID for the share.
	* @param coreId CoreID for the share.
	* @param tagId TagID for the share.
	* @param virt Virtual address of the share.
	* @param size Size of the share.
	* @return Result code.
	*/
	Result createShare(ProcessID pid,
		Size coreId,
		Size tagId,
		Address virt,
		Size size);

	/**
	* Read memory share by Process, Core and Tag IDs.
	*
	* @param share MemoryShare buffer (input/output).
	* @return Result code.
	*/
	Result readShare(MemoryShare *share);

	/**
	* Remove all shares for the given ProcessID
	*
	* @param pid ProcessID to remove all shares for
	* @return Result code
	*/
	Result removeShares(ProcessID pid);

	private:
		//Release one memory share
		Result releaseShare(MemoryShare *share, Size idx);

		//ProcessID associated to these shares
		ProcessID m_pid;

		//MemoryContext instance
		MemoryContext *m_memory;

		//Memory channel for sending kernel events to the associatd Process
		MemoryChannel * m_kernelChannel;

		//Contains all memory shares
		Index<MemoryShare> m_shares;
};