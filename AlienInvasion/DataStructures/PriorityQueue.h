#pragma once
#include "PriorityNode.h"
#include <iostream>

//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class PriorityQueue
{
    PriorityNode<T>* head;
    int count = 0;
public:
    PriorityQueue() : head(nullptr) {}

    ~PriorityQueue() {
        T tmp;
        int p;
        while (dequeue(tmp,p));
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        PriorityNode<T>* newNode = new PriorityNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {
            
            newNode->setNext(head);
            head = newNode;
            count++;
            return;
        }
       
        PriorityNode<T>* current = head;        
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext( current->getNext());
        current->setNext( newNode);    
        count++;
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        PriorityNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        count--;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        pri = head->getPri();
        return true;
    }

    int getCount() const { return count; }

    void print() const {
        cout << "[";
        PriorityNode<T>* temp = head;
        while (temp) {
            int pri;
            cout << temp->getItem(pri);
            temp = temp->getNext();
            if (temp) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};
