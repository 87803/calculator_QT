#include"sqstack.h"
#include<iostream>
using namespace std;

template<class elemType>
SqStack<elemType>::SqStack(int size)
{
    base = new elemType[size];
    top = base;
    stackSize = size;
    if (!base)
        exit(-1);
}

template<class elemType>
SqStack<elemType>::~SqStack()
{
    delete[] base;
}

template<class elemType>
bool SqStack<elemType>::push(elemType e)
{
    if (top - base >= stackSize)	//栈满
        return false;
    *(top++) = e;
    return true;
}

template<class elemType>
bool SqStack<elemType>::pop(elemType& e)
{
    if (stackEmpty())
        return false;
    e = *(--top);
    return true;
}

template<class elemType>
bool SqStack<elemType>::getTop(elemType& e)
{
    if (stackEmpty())
        return false;
    e = *(top - 1);
    return true;
}

template<class elemType>
bool SqStack<elemType>::stackEmpty()
{
    return base == top;
}
