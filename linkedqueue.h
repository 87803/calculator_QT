#pragma once

template<class elemType>
class QNode {
public:
    elemType data;
    QNode<elemType>* next;
};

template<class elemType>
class LinkedQueue {
public:
    LinkedQueue();
    ~LinkedQueue();
    bool enQueue(elemType& e);
    bool deQueue(elemType& e);
    bool queueEmpty();
    void printQueue();
private:
    QNode<elemType>* front;
    QNode<elemType>* rear;

};
