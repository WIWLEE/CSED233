#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "closed_hash_function.h"
#include "closed_hash_table.h"

using namespace std;

ClosedHashTable::ClosedHashTable(int table_size, ClosedHashFunction *hf) : table_size(table_size) {
    this->hf = hf;
    this->table = new int[this->table_size];
    this->states = new ClosedTableState[this->table_size];

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    for (int i = 0; i < this->table_size; i++) {
        this->states[i] = CLOSED_EMPTY;
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

ClosedHashTable::~ClosedHashTable() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] this->table;
    delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void ClosedHashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": ";
        if (this->states[i] == CLOSED_EMPTY) {
            out << "empty" << endl;
        }
        else if (this->states[i] == CLOSED_DELETED) {
            out << "deleted" << endl;
        }
        else if (this->states[i] == CLOSED_OCCUPIED) {
            out << this->table[i] << endl;
        }
        else {
            out << "unknown state" << endl;
        }

    }
}

void ClosedHashTable::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    int tempHf = hf->closedhashing(key);
    if (this->states[tempHf] == CLOSED_OCCUPIED)
    {
        int tempHf2 = tempHf;
        int collision = 0;
        while (this->states[tempHf2] != CLOSED_EMPTY)
        {
            collision++;
            tempHf2 = (tempHf + p(collision)) % table_size;

            if (this->states[tempHf2] == CLOSED_EMPTY)
            {
                this->table[tempHf2] = key;
                this->states[tempHf2] = CLOSED_OCCUPIED;
                break;
            }
            else {
                continue;
            }
        }
    }
    else
    {
        this->table[tempHf] = key;
        this->states[tempHf] = CLOSED_OCCUPIED;
    }
 
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void ClosedHashTable::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int tempHf = hf->closedhashing(key);

    if (this->table[tempHf] == key)
        this->states[tempHf] = CLOSED_DELETED;
    else
    {
        int tempHf2 = tempHf;
        int i = 0;
        while (table[tempHf2] != key)
        {
            i++;
            tempHf2 = (tempHf + p(i)) % table_size;

            if (this->table[tempHf2] == key)
            {
                this->states[tempHf2] = CLOSED_DELETED;
                break;
            }
            else
                continue;
        }
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
int ClosedHashTable:: p(int collision) {

    if (collision) {
        int i = collision;
        return pow(i, 2) + i + 1;
    }
    else return 0;

};
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
