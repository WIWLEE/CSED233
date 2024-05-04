#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>


sortAlg::sortAlg() {
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream& fout) {
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}

void sortAlg::quickSort(ofstream& fout, int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    // If swapping happens, print the array values after the swapping using "printArray(fout);"
    // You can freely add other functions (e.g., a function for partitioning) to either sort.cpp or sort.h.

    partitioning(fout, left, right);
    printArray(fout);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void sortAlg::partitioning(ofstream& fout, int left, int right) {

    int pivot = left;
    int cur = left + 1;
    int partition = left + 1;
    int wall = right;

    //pivot이 wall index 보다 크면 return
    if (pivot >= wall) {
        return;
    }

    //현재 current index가 wall index보다 작을때까지
    while (cur <= wall) {

        //pivot 값이 더 작으면 cur만 증가
        if (arr[pivot] <= arr[cur] && cur <= wall) {
            cur++;
        }

        //pivot 값이 더 크면 swap
        if (arr[pivot] > arr[cur] && cur <= wall) {

            int temp = arr[cur];
            arr[cur] = arr[partition];
            arr[partition] = temp;
            cur++;
            partition++;

            //첫번째가 swap해봤자 달라지는게 없으니까 print안하고 break
            if (cur - 2 == left && (wall - left >= 2))
                continue;

            printArray(fout);

        }

    }

    int temp = arr[pivot];
    arr[pivot] = arr[partition - 1];
    arr[partition - 1] = temp;

    //왼쪽, 오른쪽 part에 대한 재귀함수
    partitioning(fout, left, partition - 2);
    partitioning(fout, partition, right);

}

void sortAlg::merge(int left, int mid, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    mid = (left + right) / 2;

    int* sorted = new int[arr_size];
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            sorted[k] = arr[i];
            i++;
        }
        else if (arr[i] > arr[j])
        {
            sorted[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid)
    {
        sorted[k] = arr[i];
        k++;
        i++;
    }

    while (j <= right)
    {
        sorted[k] = arr[j];
        k++;
        j++;
    }

    int l = 0;
    for (l = left; l <= right; l++)
    {
        arr[l] = sorted[l];
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::mergeSort(ofstream& fout, int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////


    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(fout, left, mid);
        mergeSort(fout, mid + 1, right);
        merge(left, mid, right);
        printArray(fout);// DO NOT ERASE THIS LINE
    }


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}
