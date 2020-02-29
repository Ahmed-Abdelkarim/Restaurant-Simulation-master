#ifndef __QUEUE_H_
#define __QUEUE_H_

/*This code is an updated version from "Data Abstraction & Problem Solving with C++,WALLS AND MIRRORS ,SIXTH EDITION"*/

/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers, 
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

				The Node: item of type T and a "next" pointer
					------------- 
					| item| next | --->
					-------------
General Queue case:

                 frontPtr																backPtr
					\											   						/		
					 \											  					   /		
					------------- 	  ------------- 	  ------------- 	  ------------- 	  	  
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------	  
		
Empty Case:

                 frontptr	 backptr
						\	 /				
						 \	/				
					---- NULL ------


Single Node Case:
                 frontPtr	 backPtr
					\		/	
					 \	   /			
					-------- 	
					|	|nxt -->NULL
					--------	

*/

#include "Node.h"
#include <iostream>
template <typename T>
class Queue
{
private :
	
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count = 0;
public :
	Queue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);  
	bool dequeue(T& frntEntry, T value);  
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
	~Queue();
	int getQueueCount();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
Queue<T>::Queue()
{
	backPtr=nullptr;
	frontPtr=nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool Queue<T>::isEmpty() const
{
	if(frontPtr==nullptr)
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
bool Queue<T>::enqueue( const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	count++;
	return true ;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool Queue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr ;	
		
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;

	count--;
	return true;

}
template<typename T>
inline bool Queue<T>::dequeue(T& frntEntry, T value)
{
	if (isEmpty())
		return false;
	Node<T>* p = frontPtr;
	if (p->getItem() == value && frontPtr == backPtr) {
		frontPtr = frontPtr->getNext();
		frntEntry = p->getItem();
		backPtr = nullptr;
		count--;
		return true;
	}
	else if (p->getItem() == value) {
		frontPtr = frontPtr->getNext();
		frntEntry = p->getItem();
		count--;
		return true;
	}
	while (p->getNext())
	{
		if (p->getNext()->getItem() == value) {
			std::cout << "Found it \n";
			break;
		}
		p = p->getNext();
	}
	Node<T>* nodeToDeletePtr = p->getNext();
	if(nodeToDeletePtr != nullptr)
	{
		frntEntry = nodeToDeletePtr->getItem();
		p->setNext(nodeToDeletePtr->getNext());
		delete nodeToDeletePtr;
		count--;
		return true;
	}
	// Queue is not empty; remove front

	// Free memory reserved by the dequeued node
	return false;
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
bool Queue<T>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
Queue<T>::~Queue()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
int Queue<T>::getQueueCount() {
	return count;
}
/*
Function: toArray
returns an array of "T" 
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/


template <typename T>
T* Queue<T>::toArray(int& count)
{
	count=0;

	if(!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while(p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr= new T[count];
	p = frontPtr;
	for(int i=0; i<count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

#endif
