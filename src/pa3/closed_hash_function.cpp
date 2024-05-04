#include "closed_hash_function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;


int ClosedHashFunction::closedhashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int n = key_size;
    int r = index_size;
    int i = 0;
    int bit_size = 2 * n;
    
    bit = new int[bit_size];
    int mod = pow(2, r);
    return (midSquare(key,r,bit,bit_size)) % mod;
  
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
  
}


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

int ClosedHashFunction::midSquare(int key, int r, int* bit, int bit_size) {
    int i = 0;
    int value = pow(key, 2);
    for (i = 0; i < bit_size; i++) {
        bit[bit_size-i-1] = value % 2;
        value = value / 2;
    }

    int result = 0;
    for (i = 0; i < index_size; i++)
        result += bit[key_size - index_size/2 + i] * int(pow(2, index_size -1-i));

    return result; 
}

/*  Write your codes if you have additional functions  */
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
