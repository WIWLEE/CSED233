#include "open_hash_function.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int OpenHashFunction::openhashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int num = getDigit(key);
    int i = 0;
    int sum = 0;
    for (i = 0, sum=0; i < num; i++) {
        sum += key % 10;
        key = key / 10;
    }
    return sum % index_size;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////


int OpenHashFunction::getDigit(int key) {
    int num = 1;
    while (key > 9) {
        key /= 10;
        num++;
    }
    return num;
}
/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
