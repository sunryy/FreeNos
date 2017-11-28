#pragma once
#include "Assert.h"
#include "Sequence.h"
#include "Types.h"
#include "Macros.h"
#include "MemoryBlock.h"

//Default size of an Vector.
#define VECTOR_DEFAULT_SIZE 64

//Vectors are dynamically resizable Arrays.
template <class T> class Vector : public Sequence<T>
{
public:
	//Constructor.
	//Initializes the Vector with the given Size.
	Vector(Size size = VECTOR_DEFAULT_SIZE)
	{
		assert(size > 0);

		m_size = size;
		m_count = 0;
		m_array = new T[m_size];

	}

	//Copy constructor.
	Vector(const Vector<T>& a)
	{
		assert(a.m_size > 0);
		m_size = a.m_size;
		m_count = a.m_count;
		m_array = new T[m_size];

		for (Size i = 0; i < m_size; i++)
		{
			m_array[i] = a.m_array[i];
		}
	}

	//Destructor.
	~Vector()
	{
		delete[] m_array;
	}

	//Adds the given item to the Vector, if possible.

	virtual int insert(const T& item)
	{
		if (m_count==m_size)
		{
			if (!resize(m_size * 2))
			{
				return -1;
			}
		}
		m_array[m_count++] = item;
		return m_count - 1;
	}

	//Inserts the given item at the given position.
	virtual bool insert(Size position, const T& item)
	{
		//Resize the vector if needed
		if (position >= m_size)
		{
			Size increase = position > (m_size * 2) ? position : m_size * 2;
			if (!resize(m_size + increase))
			{
				return false;
			}
		}

		//Update the item count if needed
		if (position >= m_count)
		{
			m_count += (position + 1) - m_count;
		}

		//Assign the item
		m_array[position] = item;
		return true;
	}

	//Returns the item at the given position.
	virtual const T* get(Size position) const
	{
		if (position >= m_count)
		{
			return ZERO;
		}
		return &m_array[position];
	}

	//Return item at the given position as a reference.
	virtual const T& at(Size position) const
	{
		return m_array[position];
	}

	//Remove all items from the vector.
	virtual void clear()
	{
		m_count = 0;
	}

	//Removes the item at the given position.
	virtual bool removeAt(Size position)
	{
		if (position >= m_count)
		{
			return false;
		}

		//Move all consecutive items
		for (Size i = position; i < m_count - 1; i++)
		{
			m_array[i] = m_array[i + 1];
		}
		m_count--;
		return true;
	}

	//Returns the maximum size of this Vector.
	virtual Size size() const
	{
		return m_size;
	}

	//Returns the number of items inside the Vector.
	virtual Size count() const
	{
		return m_count;
	}

	//Get Vector data pointer.
	virtual const T* vector() const
	{
		return m_array;
	}

	//Resize the Vector.
	virtual bool resize(Size size)
	{
		assert(size > 0);
		T* arr = new T[size];
		if (!arr)
		{
			return false;
		}

		//Copy the old array in the new one
		//increase size to add to the Vector.
		for (Size i = 0; i < m_size; i++)
		{
			arr[i] = m_array[i];
		}

		//Clean up the old array and set the new one
		delete[] m_array;
		m_array = arr;
		m_size = size;
		return true;
	}

private:
	//The actual array where the data is stored.
	T* m_array;
	
	//The maximum size of the  array.
	Size m_size;

	//Number of used items in the array.
	Size m_count;
};