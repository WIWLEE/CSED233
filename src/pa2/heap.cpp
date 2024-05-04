#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

MinHeap::MinHeap() {
  heap_size = 0;
  heap_arr = new int[100]; // Default array of size 100
}

string MinHeap::printHeap() {
  string answer;
  for (int i = 0; i < heap_size; i++)
    answer += to_string(heap_arr[i]) + " ";

  return answer;
}

void MinHeap::insertKey(int k) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    

    heap_size++;
    int idx_cur = heap_size - 1;

    if(idx_cur== 0){

        //idx = 0�̸� swap ���� �׳� insert
        heap_arr[0] = k;
    }
    else {

        //idx�� insert �� ����
        heap_arr[idx_cur] = k;

        //������ (1/3 4/7 8 9 10) -> parent�� idx_cur-1/2�̴�
        while (heap_arr[(idx_cur - 1) / 2] > heap_arr[idx_cur]) {

            //swap
            int temp = heap_arr[idx_cur];
            heap_arr[idx_cur] = heap_arr[(idx_cur - 1) / 2];
            heap_arr[(idx_cur - 1) / 2] = temp;

            //������Ʈ
            idx_cur = (idx_cur - 1) / 2;
        }
       
    }


    return;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MinHeap::deleteMin() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    
    //������ �� ���
    int last_value = heap_arr[heap_size-1];

    if (heap_size == 0)
        return;
    else if (heap_size == 1) {
        heap_arr = { 0 };
        heap_size--;
    }
    else{

        //minheap�̹Ƿ� ù��° element�� �ּڰ��̴�.
        //���� 0 index�� ������ index ���� �����´�
        heap_arr[0] = last_value;
        heap_arr[heap_size-1] = 0;
        heap_size--;
        minHeapProp(0);

    }
    return;


  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MinHeap::minHeapProp(int i) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    //delete�� property���� �Լ��� minHeapProp���� ����ߴ�.

    int min_idx = i;

    for (int j = 0; j< heap_size; j++) {

        //left�� index�� 2i + 1, right�� indexsms 2i + 2�̴�.
        //left�� right �Ѵ� ���� ���
        if (2*i+1>heap_size-1){
            return;
        }
        //left�� �ִ� ���
        else if (2 * i + 2 > heap_size - 1) {
            if (heap_arr[2 * i + 1] < heap_arr[i])
                min_idx = 2 * i + 1;

            //swap
            int temp = heap_arr[min_idx];
            heap_arr[min_idx] = heap_arr[i];
            heap_arr[i] = temp;

            //������Ʈ
            i = min_idx;
        }
        //left�� right �� �߿� ���� ���� swap �Ѵ�.
        else if (min(heap_arr[2 * i + 1], heap_arr[2 * i + 2]) < heap_arr[i]) {

            if (heap_arr[2 * i + 1] < heap_arr[2 * i + 2])
                min_idx = 2 * i + 1;
            else min_idx = 2 * i + 2;

            //swap
            int temp = heap_arr[min_idx];
            heap_arr[min_idx] = heap_arr[i];
            heap_arr[i] = temp;

            //������Ʈ
            i = min_idx;
        }
    }


    return;


  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MinHeap::deleteElement(int i) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////


    int last_value = heap_arr[heap_size - 1];

    //minheap�̹Ƿ� ù��° element�� �ּڰ��̴�.
    //���� 0 index�� ������ index ���� �����´�
    heap_arr[i] = last_value;
    heap_arr[heap_size - 1] = 0;
    heap_size--;
    minHeapProp(i);

    return;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}