#include "tree.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

//Implement 도중 필요해서 정의한 함수들
int getHeight(Node* node, int node_value);
void transRoot(Node* node, Node* temp, int node_value);
void preorder2(Node* node, string* ans);
void inorder2(Node* node, string* ans);
void postorder2(Node* node, string* ans);
void isProper2(Node* node, string& ans, int* check);
bool isFull2(Node* node);
bool isComplete2(Node* node);



/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::getDepthHeight(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string str = this->preOrder();
    int size = str.size();
    string dep = "";
    string hei = "";
    int num1 = 0;
    int num2 = 0;
    int check = 0;
    int hei_max = 0;
    temp = _root;

    //예외처리
    for (int i = 0; i < size; i++) {
        if (str[i]-'0' == node_value)
            check++;
    }
    if (!check) {
        return "error";
    }

    //max height
    num1 = getHeight(this->_root, node_value);

    //root를 node_value쪽으로 바꾸고 height
    transRoot(this->_root, this->temp, node_value);
    num2 = getHeight(this->_root, node_value);

    //즉, dep는 max height - height이 된다.
    dep = to_string(num1 - num2);
    hei = to_string(num2);

    return dep + " " + hei;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void transRoot(Node* node, Node* temp, int node_value){
//Root위치를 바꾸는 함수

    if (temp == NULL)
        return;
    if (temp->value - '0' == node_value){
        *node = *temp;
        return;
    }
    
    transRoot(node, temp->left, node_value);
    transRoot(node, temp->right, node_value);

    return;
};

int getHeight(Node* node, int node_value) {
//높이를 얻는 함수

    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 0;
    else {
        int left = getHeight(node->left, node_value);
        int right = getHeight(node->right, node_value);
        //left, right 중에서 더 큰 값 -> maxheight
        return max(left, right) + 1;
    }
    return 0;
};


string BinaryTree::preOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string answer = "";
    preorder2(_root, &answer);
    answer.pop_back();
    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void preorder2(Node* node, string* ans) {
//preOrder의 재귀함수

    if (node == NULL)
        return;

     ans->push_back(node->value);
     ans->push_back(' ');

     preorder2(node->left, ans);
     preorder2(node->right, ans);
    
    return;
}

string BinaryTree::postOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string answer;
    postorder2(_root, &answer);
    answer.pop_back();
    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void postorder2(Node* node, string* ans) {
//postorder의 재귀함수

    if (node == NULL)
        return;

     postorder2(node->left, ans);
     postorder2(node->right, ans);

     ans->push_back(node->value);
     ans->push_back(' ');

    return;
}


string BinaryTree::inOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string answer;
    inorder2(_root, &answer);
    answer.pop_back();
    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void inorder2(Node* node, string* ans) {
//inorder의 재귀함수

    if (node == NULL)
        return;

    inorder2(node->left, ans);

    ans->push_back(node->value);
    ans->push_back(' ');

    inorder2(node->right, ans);


    return;
}


string BinaryTree::isProper() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string answer = "";
    int check = 0;
    isProper2(_root, answer, &check);

    return answer;


  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void isProper2(Node* node, string& ans, int* check) {
//isproper의 재귀함수

    if (node == NULL)
        ans = "True";
    else if (node->left == NULL && node->right == NULL)
        ans = "True";
    //만약 right or left 중에 하나라도 없으면 check++
    else if ((node->left == NULL && node->right != NULL)
        || (node->left != NULL && node->right == NULL))
    {
        (* check)++;
    }
    else {

        isProper2(node->left, ans, check);
        isProper2(node->right, ans, check);
    }

    //만약 check가 0이 아니면 false
    if (*check) ans = "False";
    else ans = "True";


}

string BinaryTree::isFull() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    
    string answer = "";

    if (isFull2(_root) == 1) answer = "True";
    else answer = "False";
      
    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool isFull2(Node* node) {
//isFull의 재귀함수

    if (node == NULL)
        return 1;
    else if (node->left == NULL && node->right == NULL)
        return 1;
    //만약 left or full 둘 중에 하나가 없으면 0 return
    else if ((node->left == NULL && node->right != NULL)
        || (node->left != NULL && node->right == NULL))
    {
        return 0;
    }
    
    //left right의 subtree에 대해서도 동시에 성립해야함
    return isFull2(node->left) && isFull2(node->right);
};

string BinaryTree::isComplete() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string answer = "";

    if (isComplete2(_root) == 1) answer = "True";
    else answer = "False";

    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool isComplete2(Node* node) {
//iscomplete의 재귀함수

    if (node == NULL)
        return 1;
    else if (node->left == NULL && node->right == NULL)
        return 1;
    else if (node->left == NULL && node->right != NULL)
    {
        return 0;
    }
    else {
        //left부터 들어가야함
        return isComplete2(node->left) && isComplete2(node->right);
    }

}