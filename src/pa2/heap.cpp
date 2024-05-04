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

        //idx = 0이면 swap 없이 그냥 insert
        heap_arr[0] = k;
    }
    else {

        //idx에 insert 후 정렬
        heap_arr[idx_cur] = k;

        //왼쪽은 (1/3 4/7 8 9 10) -> parent는 idx_cur-1/2이다
        while (heap_arr[(idx_cur - 1) / 2] > heap_arr[idx_cur]) {

            //swap
            int temp = heap_arr[idx_cur];
            heap_arr[idx_cur] = heap_arr[(idx_cur - 1) / 2];
            heap_arr[(idx_cur - 1) / 2] = temp;

            //업데이트
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
    
    //마지막 값 얻기
    int last_value = heap_arr[heap_size-1];

    if (heap_size == 0)
        return;
    else if (heap_size == 1) {
        heap_arr = { 0 };
        heap_size--;
    }
    else{

        //minheap이므로 첫번째 element가 최솟값이다.
        //따라서 0 index를 마지막 index 값을 가져온다
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

    //delete의 property유지 함수를 minHeapProp으로 사용했다.

    int min_idx = i;

    for (int j = 0; j< heap_size; j++) {

        //left의 index는 2i + 1, right의 indexsms 2i + 2이다.
        //left와 right 둘다 없는 경우
        if (2*i+1>heap_size-1){
            return;
        }
        //left만 있는 경우
        else if (2 * i + 2 > heap_size - 1) {
            if (heap_arr[2 * i + 1] < heap_arr[i])
                min_idx = 2 * i + 1;

            //swap
            int temp = heap_arr[min_idx];
            heap_arr[min_idx] = heap_arr[i];
            heap_arr[i] = temp;

            //업데이트
            i = min_idx;
        }
        //left와 right 둘 중에 작은 값과 swap 한다.
        else if (min(heap_arr[2 * i + 1], heap_arr[2 * i + 2]) < heap_arr[i]) {

            if (heap_arr[2 * i + 1] < heap_arr[2 * i + 2])
                min_idx = 2 * i + 1;
            else min_idx = 2 * i + 2;

            //swap
            int temp = heap_arr[min_idx];
            heap_arr[min_idx] = heap_arr[i];
            heap_arr[i] = temp;

            //업데이트
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

    //minheap이므로 첫번째 element가 최솟값이다.
    //따라서 0 index를 마지막 index 값을 가져온다
    heap_arr[i] = last_value;
    heap_arr[heap_size - 1] = 0;
    heap_size--;
    minHeapProp(i);

    return;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}