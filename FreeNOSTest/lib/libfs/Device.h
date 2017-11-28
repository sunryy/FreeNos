#pragma once 
#include "File.h"
//Abstract device class interface.
class Device : public File{
public:
	//Ctr
	Device(FileType type);

	//Dtr
	virtual ~Device();

	/**
	* Get unique device identifier.
	*
	* @return String object
	*/
	virtual String & getIdentifier();

	/**
	* @brief Perform device specific initialization.
	*
	* @return Error result code.
	*/
	virtual Error initialize();

	/**
	* Called when an interrupt has been triggered for this device.
	*
	* @param vector Vector number of the interrupt.
	* @return Error result code.
	*/
	virtual Error interrupt(Size vector);

protected:
	//Unique identifier for this Device.
	String m_identifier;
};