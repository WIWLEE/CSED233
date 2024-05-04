#pragma once
#include "tree.h"

using namespace std;

class BinarySearchTree: public BinaryTree {
public:
    BinarySearchTree() { };
    ~BinarySearchTree() { };

    int insertion(int key);
    int deletion(int key);
;
private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    Node* insertion2(Node* node, int key);
    Node* deletion2(Node* node, Node* parent, int key);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};