
#ifndef _NODE
#define _NODE
template < typename T>
class Node
{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
	Node<T>* prev;
public:
	Node();
	Node(const T& r_Item);
	Node(const T& r_Item, Node<T>* nextNodePtr);
	void setItem(const T& r_Item);
	void setNext(Node<T>* nextNodePtr);
	void setPrev(Node<T>* PrevPtr);
	T getItem() const;
	Node<T>* getNext() const;
	Node<T>* getPrev();
}; // end Node
#endif

template < typename T>
Node<T>::Node()
{
	next = nullptr;
	prev = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	prev = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

template<typename T>
inline void Node<T>::setPrev(Node<T>* PrevPtr)
{
	prev = PrevPtr;
}

template<typename T>
inline Node<T>* Node<T>::getPrev()
{
	return prev;
}