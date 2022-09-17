#include"BinaryTree.h"
#include<iostream>
using namespace std;

BTree::BTree()
{
    tree = NULL;
}

BTree::~BTree()
{
    deleteTree(tree);
}

void BTree::deleteTree(BtNode* t)
{
    if (t)
    {
        deleteTree(t->lChild);
        deleteTree(t->rChild);
        delete t;
    }
}


bool BTree::createTree()
{
    createTree(tree);
    return true;
}

bool BTree::createTree(BtNode*& t)
{
    char ch;
    ch = cin.get();
    if (ch == ' ')
        t = NULL;
    else
    {
        if (!(t = new BtNode))
            return false;
        t->data = ch;
        createTree(t->lChild);
        createTree(t->rChild);
    }
    return true;
}


void BTree::recursivePreOrderTraverse(string& result)
{
    recursivePreOrderTraverse(tree, result);
    //cout << "\n";
}

void BTree::recursivePreOrderTraverse(BtNode* t, string& result)
{
    if (t)
    {
        result = result + t->data + " ";//cout << t->data;
        recursivePreOrderTraverse(t->lChild, result);
        recursivePreOrderTraverse(t->rChild, result);
    }
}

void BTree::recursiveInOrderTraverse(string& result)
{
    recursiveInOrderTraverse(tree, result);
    //cout << "\n";
}

void BTree::recursiveInOrderTraverse(BtNode* t, string& result)
{
    if (t)
    {
        if ((t->data[0] == '*' || t->data[0] == '/') && t->lChild && (t->lChild->data[0] == '+' || t->lChild->data[0] == '-'))
            result = result + "( ";//cout << "(";
        recursiveInOrderTraverse(t->lChild, result);
        if ((t->data[0] == '*' || t->data[0] == '/') && t->lChild && (t->lChild->data[0] == '+' || t->lChild->data[0] == '-'))
            result = result + ") ";//cout << ")";
        result = result + t->data + " ";//cout << t->data;
        if ((t->data[0] == '*' || t->data[0] == '/') && t->rChild && (t->rChild->data[0] == '+' || t->rChild->data[0] == '-'))
            result = result + "( ";//cout << "(";
        recursiveInOrderTraverse(t->rChild, result);
        if ((t->data[0] == '*' || t->data[0] == '/') && t->rChild && (t->rChild->data[0] == '+' || t->rChild->data[0] == '-'))
            result = result + ") ";//cout << ")";
    }
}

void BTree::recursivePostOrderTraverse(string& result)
{
    recursivePostOrderTraverse(tree, result);
    //cout << "\n";
}

void BTree::recursivePostOrderTraverse(BtNode* t, string& result)
{
    if (t)
    {
        recursivePostOrderTraverse(t->lChild, result);
        recursivePostOrderTraverse(t->rChild, result);
        result = result + t->data + " ";//cout << t->data;
    }
}
