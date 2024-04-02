#pragma once
#include <iostream>
#include "LinkedQueue.h"

using namespace std;
template <class T>

class DoublyEndedQueue : public LinkedQueue <T> {

public:
	template<typename T>
	inline bool dequeueback(T& backentry)
	{

		Node <T>* Todelete = LinkedQueue<T>::backPtr;

		if (Todelete != NULL) {
			backentry = Todelete->getItem();
			LinkedQueue<T>::backPtr = Todelete->getPrev();

			if (Todelete == LinkedQueue<T>::frontPtr)	 // Special case: last node in the queue
				LinkedQueue<T>::frontPtr = nullptr;
			delete Todelete;
			return true;
		}

		else
			return false;
	}

	template <typename T>
	bool enqueuefront(const T& toaddfront) {

		Node<T>* ToAdd = new Node<T>(toaddfront);

		if (LinkedQueue<T>::backPtr == nullptr) {
			LinkedQueue<T>::backPtr = ToAdd;
			LinkedQueue<T>::frontPtr = ToAdd;
		}

		else {
			ToAdd->setNext(LinkedQueue<T>::frontPtr);
		}

		LinkedQueue<T>::frontPtr->setPrev(ToAdd);
		LinkedQueue<T>::frontPtr = ToAdd;


		return true;
	}
};