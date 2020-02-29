#pragma once
#include "Node.h"
template <typename T>
struct n // node declaration
{
	double priority;
	T info;
	struct n *next;
};

template <typename T>
class PriorityQueue
{
private:

	n<T>* backPtr;
	n<T>* frontPtr;
	int count=0;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, double pr);
	bool dequeue(T& frntEntry);
	bool dequeue(T& frntEntry, T value);
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
	~PriorityQueue();
	int getQueueCount() {
		return count;
	}
};
/////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry, double pr)
{
	count++;
	n<T>* newNodePtr = new n<T>;
	newNodePtr->info = newEntry;
	newNodePtr->priority = pr;
	if (frontPtr == nullptr || pr > frontPtr->priority)
	{
		newNodePtr->next = frontPtr;
		frontPtr = newNodePtr;
	}
	else
	{
		backPtr = frontPtr;
		while (backPtr->next != nullptr && backPtr->next->priority >= pr)
			backPtr = backPtr->next;
		newNodePtr->next = backPtr->next;
		backPtr->next = newNodePtr;
	}

	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	n<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->info;
	frontPtr = frontPtr->next;
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;
	count--;

	return true;

}
template<typename T>
inline bool PriorityQueue<T>::dequeue(T & frntEntry, T value)
{
	if (isEmpty())
		return false;
	n<T>* p = frontPtr;
	if (p->info == value) {
		frontPtr = frontPtr->next;
		frntEntry = p->info;
		return true;
	}
	while (p->next)
	{
		if (p->next->info == value) break;
		p = p->next;
	}
	n<T>* nodeToDeletePtr = p->next;
	frntEntry = p->info;
	p->next = p->next;
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool PriorityQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->info;
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/


template <typename T>
T* PriorityQueue<T>::toArray(int& count)
{
	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	n<T>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->next;
	}


	T* Arr = new T[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->info;
		p = p->next;
	}
	return Arr;
}
