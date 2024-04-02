#pragma once
#include <iostream>
#include "LinkedQueue.h"

using namespace std;
template <class T>

class DoublyEndedQueue : public LinkedQueue <T> {

public:

	using LinkedQueue<T>::frontPtr;
	using LinkedQueue<T>::backPtr;

	template<typename T>
	inline bool dequeueback(T& backentry)
	{
		
		Node <T>* Todelete = backPtr;

		if (Todelete != NULL) {
			backentry = Todelete->getItem();
			backPtr = Todelete->getPrev();

			if (Todelete == frontPtr)	 // Special case: last node in the queue
				frontPtr = nullptr;
			delete Todelete;
			return true;
		}

		else
			return false;
	}

	template <typename T>
	bool enqueuefront(const T& toaddfront) {

		Node<T>* ToAdd = new Node<T>(toaddfront);

		if (backPtr == nullptr) {
			backPtr = ToAdd;
			frontPtr = ToAdd;
		}

		else {
			ToAdd->setNext(frontPtr);
		}

		frontPtr->setPrev(ToAdd);
		frontPtr = ToAdd;


		return true;
	}
};