#pragma once
#include "FileSystem.h"
//Maximum number of device handled simultaneously by a DeviceServer.
#define DEVICE_MAX 32

//Device driver server.
//implements IPC handler to communicate with the FileSystem using
//FileSystemMessages and invokes Device functions appropriately.
class DeviceServer : public FileSystem
{
public:
	//Ctr
	DeviceServer(const char *path);

	//Dtr
	virtual ~DeviceServer();

	//Initialize DeviceServer.
	virtual Error initialize();

	//Add a Device
	void registerDevice(Device *dev, const char *path, ...);

	/**
	* @brief Register an interrupt vector for the given device.
	*
	* Appends the given Device on the internal list used
	* for interrupt processing in interruptHandler().
	*
	* @param dev Pointer to the Device to wait interrupts for.
	* @param vector Vector number of the interrupt.
	*
	* @see Device
	* @see interruptHandler
	*/
	void registerInterrupt(Device *dev, Size vector);

	/**
	* @brief Interrupt request handler.
	*
	* Invokes the interrupt callback function of
	* each Device registered for the interrupt vector.
	*
	* @param vector Interrupt number
	* @see Device
	* @see Device::interrupt
	*/
	virtual void interruptHandler(Size vector);

private:
	//Contains all Devices served by this DeviceServer.
	Vector<Device *> m_devices;

	//Registers Devices using interrupts.
	//An Vector with Lists of Devices using the interrupt vector as index.
	Vector<List<Device *> *> m_interrupts;
};