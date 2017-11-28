#pragma once
#include "Types.h"
#include "Macros.h"

//Forward declaration
struct CPUState;

//Interrupt controlloer interface.
class IntController
{
public:
	//Result codes.
	enum Result
	{
		Success,
		InvalidIRQ,
		InvalidFrequency,
		IOError,
		NotFound
	};

	//Function which is called when the CPU is interrrupted.
	typedef void Handler(struct CPUState state);

	//Constructor.
	IntController();

	/**
	* Get interrupt number base offset.
	*
	* Some interrupt controllers remap the interrupt numbers
	* to a certain base offset.
	*
	* @return Interrupt number base offset.
	*/
	// TODO: remove this function when IntController can serve hooks
	uint getBase();

	/**
	* Enable hardware interrupt (IRQ).
	*
	* @param irq Interrupt Request number.
	* @return Result code.
	*/
	virtual Result enable(uint irq) = 0;

	/**
	* Disable hardware interrupt (IRQ).
	*
	* @param irq Interrupt Request number.
	* @return Result code.
	*/
	virtual Result disable(uint irq) = 0;

	/**
	* Clear hardware interrupt (IRQ).
	*
	* Clearing marks the end of an interrupt service routine
	* and causes the controller to trigger the interrupt again
	* on the next trigger moment.
	*
	* @param irq Interrupt Request number to clear.
	* @return Result code.
	*/
	virtual Result clear(uint irq) = 0;

protected:
	//Interrupt number base offset.
	uint m_base;
};
