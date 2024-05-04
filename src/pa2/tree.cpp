#include "tree.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

//Implement ���� �ʿ��ؼ� ������ �Լ���
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

    //����ó��
    for (int i = 0; i < size; i++) {
        if (str[i]-'0' == node_value)
            check++;
    }
    if (!check) {
        return "error";
    }

    //max height
    num1 = getHeight(this->_root, node_value);

    //root�� node_value������ �ٲٰ� height
    transRoot(this->_root, this->temp, node_value);
    num2 = getHeight(this->_root, node_value);

    //��, dep�� max height - height�� �ȴ�.
    dep = to_string(num1 - num2);
    hei = to_string(num2);

    return dep + " " + hei;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void transRoot(Node* node, Node* temp, int node_value){
//Root��ġ�� �ٲٴ� �Լ�

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
//���̸� ��� �Լ�

    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 0;
    else {
        int left = getHeight(node->left, node_value);
        int right = getHeight(node->right, node_value);
        //left, right �߿��� �� ū �� -> maxheight
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
//preOrder�� ����Լ�

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
//postorder�� ����Լ�

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
//inorder�� ����Լ�

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
//isproper�� ����Լ�

    if (node == NULL)
        ans = "True";
    else if (node->left == NULL && node->right == NULL)
        ans = "True";
    //���� right or left �߿� �ϳ��� ������ check++
    else if ((node->left == NULL && node->right != NULL)
        || (node->left != NULL && node->right == NULL))
    {
        (* check)++;
    }
    else {

        isProper2(node->left, ans, check);
        isProper2(node->right, ans, check);
    }

    //���� check�� 0�� �ƴϸ� false
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
//isFull�� ����Լ�

    if (node == NULL)
        return 1;
    else if (node->left == NULL && node->right == NULL)
        return 1;
    //���� left or full �� �߿� �ϳ��� ������ 0 return
    else if ((node->left == NULL && node->right != NULL)
        || (node->left != NULL && node->right == NULL))
    {
        return 0;
    }
    
    //left right�� subtree�� ���ؼ��� ���ÿ� �����ؾ���
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
//iscomplete�� ����Լ�

    if (node == NULL)
        return 1;
    else if (node->left == NULL && node->right == NULL)
        return 1;
    else if (node->left == NULL && node->right != NULL)
    {
        return 0;
    }
    else {
        //left���� ������
        return isComplete2(node->left) && isComplete2(node->right);
    }

}