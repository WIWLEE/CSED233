#include "tree.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

Node* AVLTree::insertion2(Node* node, int key)
{
    if (node == NULL)
    {
        Node* newNode = new Node(key);
        return newNode;
    }

    // key가 더 크면 오른쪽으로
    if (key > node->key)
        node->right = insertion2(node->right, key);
    // key가 더 작으면 왼쪽으로
    if (key < node->key)
        node->left = insertion2(node->left, key);


    Update(node);

    //left->left
    if (findBF(node) > 1 && key < node->left->key)
        node = LL(node);
    //right->Right
    if (findBF(node) < -1 && key > node->right->key)
        node = RR(node);
    //left->right
    if (findBF(node) > 1 && key > node->left->key)
        node = LR(node);
    //right->left
    if (findBF(node) < -1 && key < node->right->key)
        node = RL(node);
    return node;
}

Node* AVLTree::deletion2(Node* node, Node* parent, int key)
{
    if (node == NULL)
        return node;
    else if (key < node->key)
        node->left = deletion2(node->left, node, key);
    else if (key > node->key)
        node->right = deletion2(node->right, node, key);
    else
    {
        //leaf인 경우
        if (node->left == NULL && node->right == NULL)
        {
            if (parent != NULL && parent->left == node)
                parent->left = NULL;

            else if (parent != NULL && parent->right == node)
                parent->right = NULL;

            node = NULL;
        }
        //child가 하나인 경우
        else if (node->left == NULL || node->right == NULL)
        {

            Node* temp = NULL;

            //child 정하기
            if (node->left != NULL)
                temp = node->left;
            else if (node->right != NULL)
                temp = node->right;

            //parent 정하기
            if (parent != NULL && parent->left == node)
                parent->left = temp;
            else if (parent != NULL && parent->right == node)
                parent->right = temp;

            //없애기
            node = temp;
        }
        //child가 2개인 경우
        else if (node->left != NULL && node->right != NULL)
        {
            Node* min = findMin(node->right);
            node->key = min->key;
            node->right = deletion2(node->right, node, min->key);
        }
    }

    if (node == NULL)
        return NULL;

    Update(node);

    //left->left
    if (findBF(node) > 1 && findBF(node->left) >= 0)
        node = LL(node);

    //right->right
    if (findBF(node) < -1 && findBF(node->right) <= 0)
        node = RR(node);

    //left->right
    if (findBF(node) > 1 && findBF(node->left) < 0)
        node = LR(node);

    //right->left
    if (findBF(node) < -1 && findBF(node->right) > 0)
        node = RL(node);

    return node;

}

int AVLTree::findBF(Node* node)
{
    //차이 없으면 0
    if (node->left == NULL && node->right == NULL)
        return 0;
    //둘다 있으면 height 차이 (-면 right가 크고, +면 left가 큼)
    if (node->left && node->right)
        return node->left->height - node->right->height;
    //차이나면 left 높이 +1
    if (node->left && node->right == NULL)
        return node->left->height + 1;
    //차이나면 right 높이 +1
    if (node->left == NULL && node->right)
        return -1 - node->right->height;

}

Node* AVLTree::LL(Node* node)
{

    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    Update(node);
    Update(temp);
    return temp;
}

Node* AVLTree::RR(Node* node)
{

    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    Update(node);
    Update(temp);
    return temp;
}


Node* AVLTree::RL(Node* node)
{
    node->right = LL(node->right);
    return RR(node);
}


Node* AVLTree::LR(Node* node)
{
    node->left = RR(node->left);
    return LL(node);
}

Node* AVLTree::findMin(Node* node)
{
    //재귀 조건
    if (node == NULL)
        return NULL;
    //더 이상 왼쪽 child가 없으면 node return
    if (node->left == NULL)
        return node;

    return findMin(node->left);
}


void AVLTree::Update(Node* node)
{
    //재귀 조건
    if (node == NULL)
        return;
    //leaf이면 height은 0
    else if (node->left == NULL && node->right == NULL)
        node->height = 0;
    //left child 있으면 +1
    else if (node->left != NULL && node->right == NULL)
        node->height = 1 + node->left->height;
    //right child 있으면 +1
    else if (node->left == NULL && node->right != NULL)
        node->height = 1 + node->right->height;
    //child 둘다 있으면 max값
    else if (node->left != NULL && node->right != NULL) {
        if (node->left->height > node->right->height)
            node->height = 1 + node->left->height;
        else node->height = 1 + node->right->height;
    }
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int AVLTree::insertion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Node* node = _root;

    if (node == NULL) {
        _root = insertion2(_root, key);
        return 0;
    }
    while (node)
    {
        if (key == node->key) {
            return -1;
        }
        else if (key < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }

    }
    _root = insertion2(_root, key);
    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int AVLTree::deletion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Node* node = _root;

    if (node == NULL) {
        return -1;
    }

    int check = 0;
    while (node != NULL) {

        if ((key == node->key)) {
            check++;
            break;
        }
        else if (key < node->key && node->left == NULL) {
            return -1;
        }
        else if (key < node->key) {
            node = node->left;
        }
        else if (key > node->key && node->right == NULL) {
            return -1;
        }
        else if (key > node->key) {
            node = node->right;
        }

    }

    if (check) {
        _root = deletion2(_root, NULL, key);
        return 0;
    }

    return -1;


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}