#pragma once
#include<string>
using namespace std;

class BtNode {
public:
    string data;
    BtNode* lChild;
    BtNode* rChild;
};


class BTree {
public:
    BTree();
    ~BTree();
    bool createTree();
    void deleteTree(BtNode* t);
    void recursivePreOrderTraverse(string& result);
    void recursiveInOrderTraverse(string& result);
    void recursivePostOrderTraverse(string& result);
    BtNode* tree;
private:
    bool createTree(BtNode*& t);
    void recursivePreOrderTraverse(BtNode* t, string& result);
    void recursiveInOrderTraverse(BtNode* t, string& result);
    void recursivePostOrderTraverse(BtNode* t, string& result);
};
