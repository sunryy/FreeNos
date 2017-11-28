#pragma once
#include "Container.h"
#include "Comparable.h"
#include "Types.h"
#include "Macros.h"
#include "List.h"
#include "ListIterator.h"

//Assoiatives are containers that provide a mapping of keys to values.
template <class K, class V> class Associative :public Container, public Comparable<Associative<K, V>>
{
public:
	//Inserts the given item to the Association.
	virtual bool insert(const K &key, const V &item){
		return false;
	}

	//Append the given item to the Association.
	virtual bool append(const K &key, const V &item){
		return false;
	}

	//Removes all items associated with the given key.
	virtual int remove(const K & key)
	{
		return 0;
	}

	/**
	* Removes all items from the Association
	*/
	virtual void clear()
	{
		List<K> k = keys();

		for (ListIterator<K> i(k); i.hasNext(); i++)
			remove(i.current());
	}

	/**
	* Retrieve all keys inside the Association.
	*
	* @return A List of keys.
	*/
	virtual List<K> keys() const = 0;

	/**
	* Retrieve list of Keys for the given value.
	*/
	virtual List<K> keys(const V & value) const = 0;

	/**
	* Check if the given key exists.
	*
	* @return True if exists, false otherwise.
	*/
	virtual bool contains(const K & key) const
	{
		return values(key).count() > 0;
	}

	/**
	* Retrieve all values inside the Association.
	*
	* @return A List of values.
	*/
	virtual List<V> values() const = 0;

	/**
	* Retrieve values for the given key inside the Association.
	*
	* @return A List of values.
	*/
	virtual List<V> values(const K & key) const = 0;

	/**
	* Returns the first value for the given key.
	*
	* @param key Key to find.
	* @return Pointer to the first value for the given key or ZERO if not found.
	*/
	virtual const V * get(const K & key) const = 0;

	/**
	* Returns a reference to the first value for the given key.
	* This function assumes the key exists.
	*
	* @param key Key to find.
	* @return Reference to the first value for the key.
	*/
	virtual const V & at(const K & key) const = 0;

	/**
	* Return the first value for the given key.
	* If the key is not found, the default value is returned.
	*
	* @return First value for the given key, or the defaultValue.
	*/
	virtual const V value(const K & key, const V defaultValue = V()) const = 0;

	//Compare this container to another Container.
	virtual int compareTo(const Associative<K, V> &a) const{
		Size sz = size();
		Size cnt = count();
		List<V> vals = a.values();

		//Size must be equal
		if (a.size() != sz)
		{
			return a.size() - sz;
		}

		//Count must be equal
		if (a.count() !=cnt)
		{
			return a.count() - cnt;
		}

		//All elements must be equal
		for (ListIterator<V> i(values()); i.hasCurrent(); i++)
		{
			if (!vals.contains(i.current()))
			{
				return 1;
			}
		}
		return 0;
	}

	//Returns the first value for the given key.
	const V &operator [](K key) const{
		return at(key);
	}
};