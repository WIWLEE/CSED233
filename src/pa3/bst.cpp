#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insertion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Node* node = _root;

    if (node == NULL) {
        _root = new Node(key);
        return 0;
    }

    while (node!=NULL) {

        if ((key == node->key)) {
            return -1;
        }
        else if (key < node->key && node->left==NULL) {
            node->left = insertion2(node->left, key);
            return 0;
        }
        else if (key < node->key) {
            node = node->left;
        }
        else if (key > node->key && node->right==NULL) {
            node->right = insertion2(node->right, key);
            return 0;
        }
        else if (key > node->key) {
            node = node->right;
        }

    }
    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int BinarySearchTree::deletion(int key) {
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

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */

Node* BinarySearchTree::insertion2(Node* node, int key) {

    if (node == NULL){
        
        Node* block = new Node(key);
        return block;
    }
    if (key == node->key) {
        return node;
    }
    else if (key < node->key) {
        node->left = insertion2(node->left, key);
    }
    else if (key > node->key) {
        node->right = insertion2(node->right, key);
    }

}

Node* BinarySearchTree::deletion2(Node* node, Node* parent, int key) {

    if (key == node->key)
    {
        if (node->left == NULL && node->right == NULL) 
        {
            if (parent)
            {
                if (parent->left == node)
                    parent->left = NULL;

                else if (parent->right == node)
                    parent->right = NULL;
            }

            node = NULL;
        }
        else if (node->left == NULL || node->right == NULL)
        {
           
            Node* temp = NULL;
            if (node->left != NULL)
                temp = node->left;
            else
                temp = node->right;

            if (parent)
            {
                if (parent->left == node)
                    parent->left = temp;
                else
                    parent->right = temp;
            }
            node = temp;
        }
        else if (node->left != NULL && node->right != NULL) 
        {
            Node* exchNode = node->right;
            while (exchNode->left) {
                if (exchNode->left == NULL) return NULL;
                if (exchNode == NULL) return node;
                exchNode = exchNode->left;
            }

            node = deletion2(_root, NULL, exchNode->key);
            node->key = exchNode->key;

        }
    }
    else if (key < node->key) {
        node->left = deletion2(node->left, node, key);
    }
    else if (key > node->key) {
        node->right = deletion2(node->right, node, key);
    }

    return node;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
