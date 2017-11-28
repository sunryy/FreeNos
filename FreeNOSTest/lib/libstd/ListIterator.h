#pragma once
#include "Macros.h"
#include "Iterator.h"
#include "List.h"
#include "Assert.h"

//Iterate through a List.
template <class T> class ListIterator :public Iterator<T>
{
public:
	//Class constructor.
	ListIterator(List<T> *list)
		: m_list(*list)
	{
		assertRead(list);

		m_current = ZERO;
		reset();
	}

	/**
	* Class constructor.
	*
	* @param list Reference to the List to iterate.
	*/
	ListIterator(List<T> & list)
		: m_list(list)
	{
		assertRead(list);

		m_current = ZERO;
		reset();
	}

	/**
	* Constant class constructor.
	*
	* @param list Reference to the List to iterate.
	*/
	ListIterator(const List<T> & list)
		: m_list((List<T> &) list)
	{
		assertRead(list);

		m_current = ZERO;
		reset();
	}

	//Reset the iterator.
	virtual void reset(){
		assertRead(m_list);
		m_current = m_list.head();
		m_next = m_current;
	}

	//Check if there is more on the List to iterate.
	virtual bool hasNext() const{
		return m_next != ZERO;
	}

	/**
	* Check if there is a current item on the List.
	* @return True if current item available, false otherwise.
	*/
	virtual bool hasCurrent() const
	{
		return m_current != ZERO;
	}

	/**
	* Get current item in the List.
	*
	* @return Current item.
	*/
	virtual const T & current() const
	{
		return m_current->data;
	}

	/**
	* Get current item in the List.
	*
	* @return Current item.
	*/
	virtual T & current()
	{
		return m_current->data;
	}

	/**
	* Fetch the next item.
	* This function first fetches the next item
	* and then updates the current item pointer to that item.
	* It assumes the iterator has a next item.
	*
	* @see hasNext
	* @return The next item.
	*/
	virtual T & next()
	{
		assertRead(m_current);
		assertRead(m_current->next);

		m_current = m_next;
		m_next = m_current->next;
		return m_current->data;
	}

	//Remove the current item from the List.
	virtual bool remove(){
		//Do we have a current item?
		if (!m_current)
		{
			return false;
		}
		//Update iterator administration
		class List<T>::Node *node = m_current;
		m_current = m_current->next;
		m_next = m_current;
	}

	//Increment operator.
	//this function first increment the current item
	//and then updates the next item pointer.
	virtual void operator++(int num){
		if (m_current)
		{
			m_current = m_current->next;
			if (m_current)
			{
				m_next = m_current->next;
			}
			else
			{
				m_next = ZERO;
			}
		}
	}


private:
	//Points to the List to iterate.
	List<T> &m_list;

	//Current node
	class List<T>::Node *m_current;

	//Next node
	class List<T>::Node *m_next;

};