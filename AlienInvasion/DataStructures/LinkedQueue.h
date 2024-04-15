
#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "Node.h"
#include "QueueADT.h"

#include <iostream>
using namespace std;


template <typename T>
class LinkedQueue:public QueueADT<T>
{

public :
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count = 0;

public :
	LinkedQueue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);  
	bool peek(T& frntEntry)  const;	
	int getCount() const;
	void print() const;
	~LinkedQueue();

	//copy constructor
	LinkedQueue(const LinkedQueue<T> & LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedQueue<T>::LinkedQueue()
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
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr==nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	Node<T>* PrevNode = backPtr;
	backPtr = newNodePtr;// New node is the last node now
	backPtr->setPrev(PrevNode);
	backPtr->setNext(nullptr);
	count++;
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
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	if(frontPtr) frontPtr->setPrev(nullptr);

	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		frontPtr = backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;

	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
int LinkedQueue<T>::getCount() const
{
	return count;
}

template <typename T>
void LinkedQueue<T>::print() const
{
	cout << "[";
	Node<T>* temp = frontPtr;
	while (temp) {
		T item = temp->getItem();
		if (item)
			cout << item;
		else cout << "null";
		temp = temp->getNext();
		if (temp) {
			cout << ", ";
		}
	}
	cout << "]" << endl;
}

///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;
	while (dequeue(temp));

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& LQ)
{
	frontPtr = backPtr = nullptr;
	Node<T>* NodePtr = LQ.frontPtr;	//start at the front node in LQ
	while (NodePtr)
	{
		enqueue(NodePtr->getItem());	//get data of each node and enqueue it in this queue 
		NodePtr = NodePtr->getNext();
	}
}

#endif