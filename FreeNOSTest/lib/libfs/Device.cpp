#include "Device.h"



Device::Device(FileType type)
: File(type)
{
}

Device::~Device()
{
}

String & Device::getIdentifier()
{
	return m_identifier;
}

Error Device::initialize()
{
	return ESUCCESS;
}

Error Device::interrupt(Size vector)
{
#warning why success ?
	return ESUCCESS;
}
