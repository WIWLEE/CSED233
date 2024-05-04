#pragma once
#include "bst.h"

using namespace std;

class AVLTree : public BinarySearchTree
{
public:
    AVLTree() { };
    ~AVLTree() { };

    int insertion(int key);
    int deletion(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    Node* insertion2(Node* node, int key);
    Node* deletion2(Node* node, Node* parent, int key);
  
    int findBF(Node* node);
    Node* RR(Node* root);
    Node* LL(Node* root);
    Node* RL(Node* root);
    Node* LR(Node* root);
    Node* findMin(Node* node);
    void Update(Node* node);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};