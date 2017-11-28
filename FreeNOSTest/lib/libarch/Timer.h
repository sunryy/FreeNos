#pragma once
#include "Macros.h"
#include "Types.h"

//Represents a configurable timer device.
class Timer
{
private:

public:
	//Timer information structure.
	typedef struct Info
	{
		u64 ticks;
		Size frequency;
	}
	Info;

	//Result codes.
	enum Result
	{
		Success,
		NotFound,
		IOError,
		InvalidFrequency
	};

	//Constructor
	Timer();

	//Get timer interrupt number.
	Size getInterrupt() const;

	//Get timer frequency.
	Size getFrequency() const;

	//Set timer frequency.
	virtual Result setFrequency(Size hertz);

	//Get current timer info.
	virtual Result getCurrent(Info* info);

	//Initialize the timer.
	virtual Result initialize();

	//Start the timer
	virtual Result start();

	//Stop the timer.
	virtual Result stop();

	//Process timer tick.
	virtual Result tick();

	//Busy wait a number of microseconds.
	virtual Result wait(u32 microseconds);

	//Check if a timer value is expired
	bool isExpired(const Info* info);

protected:

	//The current Timer infomation.
	Info m_info;

	//Frequency of the TImer.
	Size m_frequency;

	//Timer interrupt number.
	Size m_int;

};