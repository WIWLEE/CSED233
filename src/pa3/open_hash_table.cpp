#include <iostream>
#include <fstream>
#include <string>
#include "open_hash_function.h"
#include "open_hash_function.cpp"
#include "open_hash_table.h"

using namespace std;

OpenHashTable::OpenHashTable(int table_size, OpenHashFunction *hf) : table_size(table_size) {
    this->hf = hf;
    table = new HashNode * [this->table_size];
    for (int i = 0; i < this->table_size; i++) {
        table[i] = NULL;
    }
    this->states = new OpenTableState[this->table_size];
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    for (int i = 0; i < this->table_size; i++) //state �ʱ�ȭ
        states[i] = OPEN_EMPTY;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

OpenHashTable::~OpenHashTable() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] table;
    delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void OpenHashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": ";
        if (this->states[i] == OPEN_EMPTY){
            out << "empty" << endl;
        }else if (this->states[i] == OPEN_OCCUPIED){
          HashNode* cur;
          cur = table[i];
          while(cur->next != NULL){
              out << cur->key ;
              out << ", ";
              cur = cur->next;
          }
            out << cur->key << endl;
        }else{
            out << "unknown state" << endl;
        }
    }
}

void OpenHashTable::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int tempHf = hf->openhashing(key); 
    HashNode* tempTb = this->table[tempHf];

    if (this->states[tempHf] == OPEN_OCCUPIED) 
    {
        while (tempTb->next != NULL) {
            tempTb = tempTb->next;
        }
        tempTb->next = new HashNode(key);
    }
    else if(this->states[tempHf] == OPEN_EMPTY)
    {
        this->states[tempHf] = OPEN_OCCUPIED;
        this->table[tempHf] = new HashNode(key);
    }
    return;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void OpenHashTable::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int tempHf = hf->openhashing(key); //task 5�� hash function�� �����ؼ� mod table_size�� ���� ��
    HashNode* tempTb = this->table[tempHf];
    HashNode* parent = new HashNode(0);
    parent->next = tempTb;

    if (this->table[tempHf]->next == NULL) {
        this->states[tempHf] = OPEN_EMPTY;
        this->table[tempHf] = NULL;
    }
    else {
        while (1)
        {
            if (tempTb->key == key) {

                tempTb->key=tempTb->next->key;
                tempTb->next = tempTb->next->next;
                break;
            }
            else {
                tempTb = tempTb->next;
            }

        }
    }
   
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
void OpenHashTable::changeTableKey(int key, int tempHf) {

    this->table[tempHf]->key = key;
};
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
