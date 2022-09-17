#pragma once
#include"linkedqueue.cpp"
#include"sqstack.cpp"
#include"BinaryTree.h"

class calculator {
public:
    double getResult(string& traverseResult);
    string isExpressionLegal();
    void setInfixExpression(string ie);

private:
    void getReversePolishNotation();//中缀表达式转换为后缀表达式存入队列中
    void dealNegativeNum();//处理中缀表达式中的负数，便于后续转换
    void createExpressionTree(BTree& bt);
    string getTraverseResult();
    double calculateResult();
    LinkedQueue<string>* RPN;//存储后缀表达式
    string infixExpression;//存输入的中缀表达式
};

