#pragma once

template<class elemType>
class SqStack {
public:
    SqStack(int size=500);
    ~SqStack();
    bool push(elemType e);
    bool pop(elemType& e);
    bool getTop(elemType& e);
    bool stackEmpty();

private:
    elemType* base;
    elemType* top;
    int stackSize;
};
