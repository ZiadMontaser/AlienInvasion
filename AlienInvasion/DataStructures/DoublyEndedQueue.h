#pragma once

#include "LinkedQueue.h"

template < class T>

class DoublyEndedQueue : public <T> LinkedQueue {

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

};