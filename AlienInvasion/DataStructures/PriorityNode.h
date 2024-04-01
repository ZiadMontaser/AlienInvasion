#pragma once
template < typename T>
class PriorityNode
{
private :
	T item;		// A data item
	int pri;	//priority of the item
	PriorityNode<T>* next; // Pointer to next node
public :
	PriorityNode(const T& r_Item, int PRI)
	{
		setItem(r_Item, PRI);
		next = nullptr;
	}
	void setItem(const T& r_Item, int PRI)
	{
		item = r_Item;
		pri = PRI;
	}
	void setNext(PriorityNode<T>* nextNodePtr)
	{		next = nextNodePtr; 	}
	
	T getItem(int& PRI) const
	{
		PRI = pri;
		return item;
	}
	
	PriorityNode<T>* getNext() const 
	{		return next;	}
	
	int getPri() const
	{		return pri; 	}
}; // end Node

