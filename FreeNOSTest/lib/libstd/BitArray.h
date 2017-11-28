#pragma once
#include "Macros.h"
#include "Assert.h"
#include "Types.h"

//Macro to convert number of bits to bytes
#define BITS_TO_BYTES(bits) ((bits / 8) + ((bits & 8) ? 1 : 0))

//Represents an array of bits.
class BitArray
{
public:
	//Result codes.
	enum Result
	{
		Success,
		InvalidArgument,
		OutOfMemory
	};

	//Class constructor.
	BitArray(Size size, u8 *array = ZERO);

	//Class destructor.
	~BitArray();

	//Returns the maximum size of this Container.
	Size size() const;

	//Get the number of bits in the map which have the given value.
	Size count(bool on) const;

	//Sets the given bit to the given value.
	void set(Size bit, bool value = true);

	//Set a range of bits inside the map to 1.
	void setRange(Size from, Size to);

	//Sets the next unset bit(s).
	Result setNext(Size *bit, Size count = 1, Size offset = 0, Size boundary = 1);

	//Sets the given bit to zero.
	void unset(Size bit);

	//Set all bits to zero.
	void clear();

	//Verify if a given bit is set.
	bool isSet(Size bit) const;

	//Retrieve a pointer to the internal BitArray.
	u8 *array() const;

	//Use the given pointer as the BitArray buffer.
	void setArray(u8 *array, Size size = ZERO);

	//Retrieve the value of the given bit.
	bool operator[] (Size bit) const;

	//Retrieve the value of the given bit.
	bool operator[](int bit) const;

private:
	//Total number of bits in the array.
	Size m_size;

	//Set bits in the array.
	Size m_set;

	//Array containing the bits.
	u8 *m_array;

	//True if m_array was allocated interally.
	bool m_allocated;
};