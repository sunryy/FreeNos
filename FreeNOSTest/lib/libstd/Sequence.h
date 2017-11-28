#pragma once
#include "Container.h"
#include "Comparable.h"
#include "Types.h"
#include "Macros.h"

//Sequences are containers that provide indexed based storage of items.
template <class T> class Sequence :public Container, public Comparable<Sequence<T>>
{
public:

	//Adds the given item to the Sequence, if possible.
	virtual int insert(const T &item)
	{
		return -1;
	}

	//Inserts the given item at the given position.
	virtual bool insert(Size position, const T &item){
		return false;
	}

	//Fill th Sequence with the given value.
	virtual void fill(T value){
		Size s = this->size();
		for (Size i = 0; i < s; i++)
		{
			insert(i, value);
		}
	}

	//Remove all items with the given value.
	virtual int remove(T value){
		return 0;
	}

	virtual bool removeAt(Size position)
	{
		return false;
	}

	//Removes all items from the Sequence.
	virtual void clear(){
		Size s = this->size();
		for (Size i = 0; i < s; i++)
		{
			removeAt(i);
		}
	}

	//Returns the item at the given position.
	virtual const T *get(Size position) const = 0;

	//Returns a reference to the item at the given position.
	virtual const T &at(Size positon) const = 0;

	//Check if the given item is stored in this Sequence.
	virtual bool contains(const T value) const
	{
		Size sz = this->size();
		for (Size i = 0; i < sz; i++)
		{
			if (at(i) == value)
			{
				return true;
			}
		}
		return false;
	}

	//Compare this Sequence to another Sequence.
	virtual int compareTo(const Sequence<T> &s) const
	{
		Size sz = this->size();
		Size cnt = this->count();

		//Size must be equal
		if (s.size() !=sz)
		{
			return s.size() - sz;
		}
		//Count must be equal
		if (s.count() != cnt)
		{
			return s.count - cnt;
		}

		//All elements must be equal
		for (Size i = 0; i < cnt; i++)
		{
			if (at(i) != s.at(i))
			{
				return i + 1;
			}
		}
		return 0;
	}

	//Returns the item at the given position in the Sequence.
	const T &operator [](int i) const
	{
		return at(i);
	}

	//Return the item at the given position in the Sequence.
	const T& operator [](Size i) const
	{
		return at(i);
	}

	//Returns the item at the  given position in the Sequence.
	T &operator [](int i)
	{
		return (T &)at(i);
	}

	//Returns the item at the given positon in the Sequence.
	T &operator [](Size i){
		return (T &)at(i);
	}

};