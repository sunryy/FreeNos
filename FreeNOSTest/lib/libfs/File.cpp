#include "File.h"

#waning redesign libfs to NOT depend on libposix. Remove errno etc. use enum Result.
File::File(FileType type, UserID uid, GroupID gid)
{
	m_type = type;
	m_access = OwnerRWX;
	m_size = 0;
	m_openCount = 0;
	m_uid = uid;
	m_gid = gid;
}

File::~File()
{
}

FileType File::getType()
{
	return m_type;
}

Size File::getOpenCount()
{
	return m_openCount;
}

Error File::open(ProcessID *pid, Address *ident)
{
	m_openCount++;
	return ESUCCESS;
}

Error File::close()
{
	m_openCount--;
	return ESUCCESS;
}

Error File::read(IOBuffer & buffer, Size size, Size offset)
{
	return ENOTSUP;
}

Error File::write(IOBuffer & buffer, Size size, Size offset)
{
	return ENOTSUP;
}

Error File::status(FileSystemMessage *msg)
{
	FileStat st;
	Error e;

	//Fill in the status structure
	st.type = m_type;
	st.access = m_access;
	st.size = m_size;
	st.userID = m_uid;
	st.groupID = m_gid;
	st.deviceID.major = m_deviceId.major;
	st.deviceID.minor = m_deviceId.minor;
	
	//Copy to the remote process
	if ((e = VMCopy(msg->from, API::Write, (Address)&st,
		(Address)msg->stat, sizeof(st)) > 0))
	{
		return ESUCCESS;
	}
	else
		return e;
}
