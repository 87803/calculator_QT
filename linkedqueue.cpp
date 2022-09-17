#include"linkedqueue.h"
#include<iostream>
using namespace std;

template<class elemType>
LinkedQueue<elemType>::LinkedQueue()
{
    front = NULL;
    rear = NULL;
}

template<class elemType>
LinkedQueue<elemType>::~LinkedQueue()
{
    while (front&&front->next)
    {
        QNode<elemType>* temp = front;
        front = front->next;
        delete temp;
    }
    delete front;
    front = NULL;
}

template<class elemType>
bool LinkedQueue<elemType>::enQueue(elemType& e)
{
    QNode<elemType>* temp = new QNode<elemType>;
    if (!temp)
        return false;
    temp->data = e;
    temp->next = NULL;
    if (!front)
    {
        front = temp;
        rear = temp;
        return true;
    }
    rear->next = temp;
    rear = temp;
    return true;
}

template<class elemType>
bool LinkedQueue<elemType>::deQueue(elemType& e)
{
    if (!front)
        return false;
    e = front->data;
    QNode<elemType>* temp = front;
    front = front->next;
    delete temp;
    if (!front)
        rear = NULL;
    return true;
}

template<class elemType>
bool LinkedQueue<elemType>::queueEmpty()
{
    return !front;
}

template<class elemType>
void LinkedQueue<elemType>::printQueue()
{
    QNode<elemType>* temp=front;
    while (temp)
    {
        cout << temp->data;
        temp = temp->next;
    }

}
