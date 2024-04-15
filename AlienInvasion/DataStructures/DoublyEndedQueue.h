#pragma once
#include <iostream>
#include "LinkedQueue.h"

using namespace std;
template <class T>

class DoublyEndedQueue : public LinkedQueue <T> {

public:

	using LinkedQueue<T>::frontPtr;
	using LinkedQueue<T>::backPtr;
	using LinkedQueue<T>::count;

	template<typename T>
	inline bool dequeueback(T& backentry)
	{
		if (LinkedQueue<T>::isEmpty()) return false;

		Node <T>* Todelete = backPtr;

		if (Todelete != NULL) {
			backentry = Todelete->getItem();
			backPtr = Todelete->getPrev();
			
			if (Todelete == frontPtr)	 // Special case: last node in the queue
				backPtr = frontPtr = nullptr;

			if(backPtr) backPtr->setNext(nullptr);
			delete Todelete;
			count--;
			return true;
		}

		else
			return false;
	}

	template <typename T>
	bool enqueuefront(const T& toaddfront) {

		Node<T>* ToAdd = new Node<T>(toaddfront);
		ToAdd->setNext(nullptr);
		if (backPtr == nullptr) {
			backPtr = ToAdd;
			frontPtr = ToAdd;
		}

		else {
			ToAdd->setNext(frontPtr);
		}

		frontPtr->setPrev(ToAdd);
		frontPtr = ToAdd;

		count++;
		return true;
	}
};