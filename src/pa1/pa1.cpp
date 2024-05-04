#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//문제3 노드 생성
struct node {

    string command;
    int data;
    int order;
    struct node* next;
};
typedef struct node NODE;

//문제3 리스트 생성
struct list {

    NODE* head;
    int count;
};
typedef struct list LIST;

//문제4 노드 생성
struct node2 {

    char data;
    struct node2* next;

};
typedef struct node2 NODE2;

//문제4 STACK 생성
struct stack {

    int count;
    NODE2* top;

};
typedef struct stack STACK;

//문제 5 QUEUE 생성
struct queue {

    int count;
    NODE2* front;
    NODE2* rear;

};
typedef struct queue QUEUE;


/*
    [Task 1] Choose the TIGHT bound of the following arraySum function

    *arraySum*
        Input
        - int n: the length of the input arrays (n >=1)
        - int* A: an array storing n >= 1 integers
        Output
        - int: Sum of given array A
        int arraySum(int n, int* A) {
            int currSum = 0;
            for (int i = 0; i < n; i++)
                currSum += A[i];
            return currSum;
        }


    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream& fout) {
    int answer = 2; // TODO: Change to your answer

    fout << "[Task 1]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 2] Choose the TIGHT bound of the following primeSearch function

    *primeSearch*
        Input
        - int n: input number for ending range
        Output
        - int numPrimes: The total number of prime numbers less than n
        int primeSearch(int n) {
            int numPrimes = 0;
            int ctr = 0;
            for (int i = 0; i < n; i++) {
                for(int j = 2; j <= sqrt(i); j++) {
                    if(i % j == 0) {
                        ctr++;
                        break;
                    }
                }
                if(ctr == 0 && i > 1)
                    numPrimes++;
                ctr=0;
            }
            return numPrimes;
        }


    Choices
        1: O( log(n) )
        2: O( n log(n) )
        3: O( n^(1/2) )
        4: O( n*n^(1/2) )
*/
void task_2(ofstream& fout) {
    int answer = 4; // TODO: Change to your answer

    fout << "[Task 2]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or delete an integer into the list.
        An user can insert or delete an element at the specific index.
        If the specified index is out of range of the given list, print “error”.

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,index): insert “# of elements in the current list” at the
   index in the list. index indicates zero-based index.
        - (‘delete’,index): delete an element at the index in the list. index
   indicates zero-based index.

    Output:
        - An array after insertion/deletion in a string separated with the
   spacebar
        - “error” if the index is out of range
*/

void task_3(ofstream& fout, InstructionSequence* instr_seq) {
    string answer;

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    //리스트 생성
    LIST list;
    list.head = NULL;
    list.count = 0;

    for (int i = 0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;

        //insert
        if (command.compare("insert") == 0) {
            /* TODO: Implement */

            //예외처리
            if (instr_seq->instructions[i].value <0 || instr_seq->instructions[i].value>list.count) {
                answer.clear();
                answer = "error";
                list.count = 0;

                break;
            }

            //입력값을 받은 빈 노드 (temp) 생성
            NODE* temp = (NODE*)malloc(sizeof(NODE));
            temp->data = list.count;
            temp->order = instr_seq->instructions[i].value;

            //이전노드 가르키는 pPre 생성
            NODE* pPre = list.head;
            for (int j = 1; j < instr_seq->instructions[i].value; j++)
                pPre = pPre->next;

            //order가 0이어도 무조건 pPre = NULL이 되어야함
            if (temp->order == 0) pPre = NULL;

            //맨 앞이나 빈 LIST에 삽입할 경우
            if (pPre == NULL) {
                temp->next = list.head;
                list.head = temp;
            }
            else //중간이나 맨 뒤에 삽입할 경우
            {
                temp->next = pPre->next;
                pPre->next = temp;
            }
            list.count++;

        }
        //delete
        else if (command.compare("delete") == 0) {

            //예외처리
            if (instr_seq->instructions[i].value < 0 || instr_seq->instructions[i].value >= list.count) {
                answer.clear();
                answer = "error";
                list.count = 0;

                break;
            }

            //이전노드 가르키는 pPre 생성
            NODE* pPre = list.head;
            for (int j = 1; j < instr_seq->instructions[i].value; j++)
                pPre = pPre->next;

            //삭제노드 가르키는 pPos 생성
            NODE* pPos = list.head;
            for (int j = 0; j < instr_seq->instructions[i].value; j++)
                pPos = pPos->next;

            //order가 0이어도 무조건 pPre = NULL이 되어야함
            if (instr_seq->instructions[i].value == 0) pPre = NULL;

            //첫번째 노드 삭제하기
            if (pPre == NULL) {

                list.head = pPos->next;
                free(pPos);

            }
            else { //나머지(중간, 마지막) 노드 삭제하기

                pPre->next = pPos->next;
                free(pPos);
            }
            list.count--;

        }
        else {

            cerr << "Invalid command" << endl;
            exit(-1);
        }

    }
    //list 출력하기
    for (int i = 0; i < list.count; i++) {
        string num = to_string(list.head->data);
        answer.append(num);
        if ((i + 1) < list.count)
            answer.append(" ");
        list.head = list.head->next;
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    fout << "[Task 3]" << endl;
    fout << answer << endl;



}

/*
    [Task 4] Stack

    Description:
        Implement a function that prints the top values of the stack when “top”
   operation is called after the sequence of “push” or “pop” operations. If the
   stack is empty, and the “top” operation is called, then print “-1”, If “pop”
   operation from the empty stack then print “error”

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’,integer): push integer into the current stack (integer is
   always positive)
        - (‘pop’,NULL): pop the top value of the current stack (this operation
   will print nothing)
        - (‘top’,NULL): print the top value of the current stack (print ‘-1’ if
   the current stack is empty)

    Output:
        - Expected printed values after processing the whole sequence, in a
   string separated with the spacebar
        - “error” if the pop operation is executed on an empty stack
*/

void task_4(ofstream& fout, InstructionSequence* instr_seq) {
    string answer;

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    //스택 생성하기
    STACK* Stack = (STACK*)malloc(sizeof(STACK));
    Stack->count = 0;
    Stack->top = NULL;

    int check = 0;

    for (int i = 0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;

        //push
        if (command.compare("push") == 0) {
            /* TODO: Implement */

            //temp 생성
            NODE2* temp = (NODE2*)malloc(sizeof(NODE2));
            temp->data = instr_seq->instructions[i].value;
            temp->next = Stack->top;

            //빈 스택에 삽입하는 경우, 아닌경우
            Stack->top = temp;
            Stack->count++;

        }
        //pop
        else if (command.compare("pop") == 0) {
            /* TODO: Implement */

            //error 예외처리
            if (Stack->count == 0) {
                answer.clear();
                answer.append("error");
                break;
            }

            char pop_data = Stack->top->data;
            NODE2* temp = Stack->top;

            //노드가 1개 남은 경우, 나머지 경우
            Stack->top = temp->next;
            Stack->count--;

        }
        //top
        else if (command.compare("top") == 0) {
            /* TODO: Implement */

            //스페이스 작업
            if (check > 0)
                answer.append(" ");
            check++;

            //-1 예외처리
            if (Stack->count <= 0) {
                answer.append("-1");
                continue;
            }
            answer.append(to_string(Stack->top->data));

        }
        else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    fout << "[Task 4]" << endl;
    fout << answer << endl;

}

/*
    [Task 5] Que-+ue

    Description:
        Implement a function which shows the value of a queue after the sequence
   of arbitrary queue operation. If the queue after the operations is empty,
   print “empty”. If “dequeue” operates on an empty queue, print “error”.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue

    Output
        - Values in the queue from the head to the tail, in a string separated
   with spacebar
        - “empty” if the queue is empty
        - “error” if the “dequeue” operation is executed on an empty queue
*/

void task_5(ofstream& fout, InstructionSequence* instr_seq) {
    string answer;

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    //Queue 생성
    QUEUE* Queue = (QUEUE*)malloc(sizeof(QUEUE));
    Queue->count = 0;
    Queue->front = NULL;
    Queue->rear = NULL;

    int check = 0;

    for (int i = 0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        int value = instr_seq->instructions[i].value;

        //enqueue
        if (command.compare("enqueue") == 0) {

            //temp 노드 생성
            NODE2* temp = (NODE2*)malloc(sizeof(NODE2));
            temp->data = instr_seq->instructions[i].value;
            temp->next = NULL;

            //빈 큐에 삽입하는 경우
            if (Queue->count == 0) {
                Queue->front = temp;
                Queue->rear = temp;
                Queue->count++;
            }
            else {
                //나머지 경우
                Queue->rear->next = temp;
                Queue->rear = temp;
                Queue->count++;
            }

        }
        else if (command.compare("dequeue") == 0) {

            //예외처리
            if (Queue->count <= 0) {
                answer.clear();
                answer.append("error ");
                check++;
                break;
            }

            NODE2* temp;
            char data = Queue->front->data;
            temp = Queue->front;


            if (Queue->count == 1) {
                //노드가 1개 남은 경우
                Queue->front = NULL;
                Queue->rear = NULL;
                Queue->count--;
            }
            else {
                //나머지 경우
                Queue->front = Queue->front->next;
                Queue->count--;

            }

        }
        else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }


    //예외처리
    if (Queue->count == 0 && check == 0) {
        answer.clear();
        answer.append("empty ");
    }

    //answer 넣기
    while (Queue->front != NULL) {
        answer.append(to_string(Queue->front->data));
        Queue->front = Queue->front->next;
        answer.append(" ");
    }
    //스페이스 맨 뒤 빼기
    answer.pop_back();

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    fout << "[Task 5]" << endl;
    fout << answer << endl;
}

/*
    [Task 6] Circular Queue

    Description:
        - a.	Implement a function which shows the value in the circular queue
   from the head to tale. If “enqueue” operates on full or “dequeue” operates
   on an empty queue, no change would happen.

    Input:
        Sequence of commands, which is one of the following,
        -(‘enqueue’,integer): enqueue integer into the current queue
        -(‘dequeue’,NULL): dequeue integer into the current queue

    Output:
        - Values in the queue from the head to the tail, in a size of 4.
   string separated with the spacebar, empy memory shows NULL -	No
   pointer movement if dequeue on empty, enqueue on full queue

*/

void task_6(ofstream& fout, InstructionSequence* instr_seq) {
    string answer;

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    //4원소의 원형 queue 만들기

    int rear = 0;
    int front = 0;
    int circular_Queue[4] = { 0,0,0,0 };

    int count = 0;

    for (int i = 0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;

        //empty, full인 경우 예외처리
        int isEmpty = 0;
        int isFull = 0;

        if (count == 0)
            isEmpty = 1;
        else if ((rear + 1) % 4 == front)
            isFull = 1;

        //enqueue
        if (command.compare("enqueue") == 0) {
            /* TODO: Implement */

            if (isFull)
                continue;
            if (isEmpty)
                front = (front + 1) % 4;
            rear = (rear + 1) % 4;
            circular_Queue[rear] = instr_seq->instructions[i].value;
            count++;


        }
        //dequeue
        else if (command.compare("dequeue") == 0) {
            /* TODO: Implement */
            if (isEmpty)
                continue;
            circular_Queue[front] = 0;
            if (count == 1)
                count--;
            else {
                front = (front + 1) % 4;
                count--;
            }
        }
        else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }

    //front부터 rear까지 출력
    for (int i = 0; i < count; i++) {
        answer.append(to_string(circular_Queue[front % 4]));
        answer.append(" ");
        front++;
    }
    if (count)
        answer.pop_back();
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    fout << "[Task 6]" << endl;
    fout << answer << endl;
}

int main(int argc, char** argv) {
    string filename = "submit.txt";
    int task_num = 0;
    InstructionSequence* instr_seq = NULL;

    // Open file
    ofstream fout;
    fout.open(filename, fstream::app);
    if (!fout.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    // Choosing task number. Default is running ALL tasks (0)
    if (argc >= 2)
        task_num = atoi(argv[1]);
    if (argc >= 3) {
        try {
            instr_seq = ParseInstructions(argv[2]);
        }
        catch (const char* e) {
            cerr << e << endl;
            return -1;
        }
    }

    // Running the task(s)
    switch (task_num) {
    case 1:
        task_1(fout);
        break;
    case 2:
        task_2(fout);
        break;
    case 3:
        task_3(fout, instr_seq);
        break;
    case 4:
        task_4(fout, instr_seq);
        break;
    case 5:
        task_5(fout, instr_seq);
        break;
    case 6:
        task_6(fout, instr_seq);
        break;
    case 0:
        task_1(fout);

        task_2(fout);

        InstructionSequence* instr_seq_3;
        instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
        task_3(fout, instr_seq_3);

        InstructionSequence* instr_seq_4;
        instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
        task_4(fout, instr_seq_4);

        InstructionSequence* instr_seq_5;
        instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
        task_5(fout, instr_seq_5);

        InstructionSequence* instr_seq_6;
        instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
        task_6(fout, instr_seq_6);
        break;
    default:
        cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
