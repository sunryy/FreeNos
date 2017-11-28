#pragma once
#include "Assert.h"
#include "Types.h"
#include "Macros.h"
#include "Sequence.h"

//Index is a resizable array of pointers to items.
template <class T> class Index :public Sequence<T>
{
public:
	//Constructor.
	Index(Size size = INDEX_DEFAULT_SIZE)
	{
		m_size = size;
		m_count = 0;
		m_array = new T*[size];

		for (Size i = 0; i < size; i++)
		{
			m_array[i] = ZERO;
		}
	}

	//Destructor.
	~Index()
	{
		delete[] m_array;
	}

	//Adds the given item to the Sequence , if possible.
	virtual int insert(const T& item)
	{
		if (m_count == m_size)
		{
			this->resize(m_size * 2);
		}
		for (Size i = 0; i < m_size;i++)
		{
			if (!m_array[i])
			{
				m_array[i] = (T*)&item;
				m_count++;
				return (int)i;
			}
		}
	}

	//Insert the given item at th given position.
	virtual bool insert(Size position, const T& item)
	{
		if (position <= m_size)
		{
			this->resize(position * 2);
		}

		if (!m_array[position])
		{
			m_count++;
		}

		m_array[position] = (T*)&item;
		return true;
	}

	//Fill the Sequence with the given value.
	virtual void fill(T value)
	{
		return;
	}

	//Removes the item at the given position.
	virtual bool remove(Size position)
	{
		if (position >= m_size)
		{
			return false;
		}

		if (!m_array[position])
		{
			return false;
		}
		m_array[position] = ZERO;
		m_count--;
		return true;
	}

	//Returns the item at the given position.
	virtual const T* get(Size position) const
	{
		if (position >= m_size)
		{
			return ZERO;
		}
		return m_array[position];
	}

	//Returns a reference to the item at the given position.
	virtual const T& at(Size position) const
	{
		return (*m_array[position]);
	}

	//Check if the given item is stored in this Sequence.
	virtual bool contains(T value)
	{
		for (Size i = 0; i < m_size; i++)
		{
			if (m_array[i] && (*m_array[i]) == value)
			{
				return true;
			}
		}
		return false;
	}

	//Compare this Sequence to another Sequence.
	virtual int compareTo(const Index<T>& idx) const
	{
		Size sz = this->size();
		Size cnt = this->count();
		//Size must be equal
		if (idx.size() != sz)
		{
			return idx.size - sz;
		}
		//Count must be equal
		if (idx.count() != cnt)
		{
			return idx.count() - cnt;
		}
		//All elements must equal
		for (Size i = 0; i < cnt; i++)
		{
			if (!(idx.m_array[i] && m_array[i] &&(*idx.m_array[i])== (*m_array[i])))
			{
				return i + 1;
			}
		}
		return 0;
	}

	//Size of the index
	virtual Size size() const
	{
		return m_size;
	}

	//Item count of the index.
	virtual Size count() const
	{
		return m_count;
	}


private:
	//Array of pointers to items.
	T** m_array;

	//Size of the pointer array.
	Size m_size;

	//Amount of valid pointers in the array.
	Size m_count;
};