#pragma once
#include "Macros.h"
#include "Types.h"
#include "Iterator.h"
#include "ListIterator.h"
#include "HashTable.h"
#include "Assert.h"

//Iterator through a HashTable.
template <class K, class V> class HashIterator : public Iterator<V>
{
public:
	//Class constructor.
	HashIterator(HashTable<K, V> &hash)
		: m_hash(hash), m_keys(hash.keys()), m_iter(m_keys)
	{
		assertRead(hash);
	}

	/**
	* Destructor.
	*/
	virtual ~HashIterator()
	{
	}

	/**
	* Reset the iterator.
	*/
	virtual void reset()
	{
		m_iter.reset();
	}

	/**
	* Check if there is more to iterate.
	* @return true if more items, false if not.
	*/
	virtual bool hasNext() const
	{
		return m_iter.hasNext();
	}

	/**
	* Check if there is a current item.
	*
	* @return True if the iterator has a current item, false otherwise.
	*/
	virtual bool hasCurrent() const
	{
		return m_iter.hasCurrent();
	}

	/**
	* Get the current value (read-only).
	*
	* @return Reference to the current read-only value.
	*/
	virtual const V & current() const
	{
		return m_hash[m_iter.current()];
	}

	/**
	* Get the current value.
	*
	* @return Reference to the current value.
	*/
	virtual V & current()
	{
		return m_hash[m_iter.current()];
	}

	/**
	* Get the current key.
	*
	* @return Reference to the current key.
	*/
	virtual const K & key()
	{
		return m_iter.current();
	}

	/**
	* Fetch the next item.
	* This function first fetches the next item
	* and then updates the current item pointer to that item.
	*
	* @return Reference to the next item.
	*/
	virtual V & next()
	{
		return m_hash[m_iter.next()];
	}

	/**
	* Remove the current item from the underlying Container.
	*
	* @return True if removed successfully, false otherwise.
	*/
	virtual bool remove()
	{
		K key = m_iter.current();
		m_iter.remove();
		return m_hash.remove(key);
	}

	/**
	* Increment operator.
	* This function first increment the current item
	* and then updates the next item pointer.
	*/
	virtual void operator ++(int num)
	{
		m_iter++;
	}



private:
	//Points to the HashTable to iterator.
	HashTable<K, V> &m_hash;

	//List of keys to iterator.
	List<K> m_keys;

	//Iterator of keys.
	ListIterator<K> m_iter;
};