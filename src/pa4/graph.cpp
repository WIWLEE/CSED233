#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647 
using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */

//가장 우선순위가 낮은 노드 찾는 함수
int Graph::findMin(string* visited, int ind)
{
    if (ind == 0)
    {
        int min = 0;

        for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        {
            //min값보다 크고, mark되어있지 않으며 변경
            if (GraphNodeList.NList[min]->vertexName > GraphNodeList.NList[i]->vertexName && GraphNodeList.NList[i]->isMarked == 0)
                min = i;
        }

        return min;
    }

    if(ind != 0)
    {
        string haveToVisit[NodeMaxCount];
        int index = 0;


        for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        {
            //mark되어 있지 않으면 Visit해야하는 배열
            if (GraphNodeList.NList[i]->isMarked == 0)
            {
                haveToVisit[index++] = GraphNodeList.NList[i]->vertexName;
            }
        }

        int min = 0;

        //마찬가지로 min이 더 크면 변경
        for (int i = 0; i < index; i++)
        {
            if (haveToVisit[min] > haveToVisit[i])
                min = i;
        }


        //target은 Visit해야하는 배열 중 가장 작은 값
        string target = haveToVisit[min];
        //그 index를 return
        int t = findNode(target);

        return t;
    }
}

//가장 우선순위가 낮은 노드 찾는 함수 2
string Graph::findMin(string nodeName, string* visited, int ind)
{

    int target = 0;
    int cnt = 0;

    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        //target에 찾는 index 넣기
        if (nodeName == GraphNodeList.NList[i]->vertexName)
        {
            target = i;
            break;
        }
    }

    Node* temp = GraphNodeList.NList[target]->adj;
    string Visit[NodeMaxCount];

    while (temp != NULL)
    {
        // adj list가 NULL이 아니고 방문하지 않았으면 방문해야 하는 visit 추가
        if (isVisited(temp->vertexName, visited, ind) == 0)
        {
            Visit[cnt++] = temp->vertexName;
        }

        temp = temp->adj;
    }

    string t = "";

    if (cnt != 0)
    {
        t = Visit[0];

        for (int i = 1; i < cnt; i++)
        {
            if (t > Visit[i])
                t = Visit[i];
        }

    }
    return t;
}

//node의 data를 통해 index를 알아내는 함수
int Graph::findNode(string nodeName)
{
    int t = 0;

    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        if (nodeName == GraphNodeList.NList[i]->vertexName)
        {
            t = i;
        }
    }

    return t;
}

//DFS 보조 함수
void Graph::DFS2(string* answer, int t, string* visited, int* visitInd)
{

    GraphNodeList.NList[t]->isMarked = 1;
    (*answer).append(GraphNodeList.NList[t]->vertexName);
    (*answer).append(" ");

    visited[(*visitInd)] = GraphNodeList.NList[t]->vertexName;
    (*visitInd)++;


    string check = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);

    while (check!= "")
    {
        string target = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);
        int t1 = findNode(target);
        DFS2(answer, t1, visited, visitInd);

        check = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);
    }
}

//DFS를 통해 CYCLE 찾는 함수
void Graph::DFS2_cycle(string* answer, int t, string* visited, int* visitInd)
{

    GraphNodeList.NList[t]->isMarked = 1;
    answer->append(GraphNodeList.NList[t]->vertexName);

    visited[(*visitInd)] = GraphNodeList.NList[t]->vertexName;
    (*visitInd)++;

    string check = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);

    while (check != "")
    {
        string target = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);
        int t1 = findNode(target);
        DFS2_cycle(answer, t1, visited, visitInd);

        check = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);
    }
}

//방문 여부 bool 함수
bool Graph::isVisited(string nodeName, string* visited, int ind)
{
    for (int i = 0; i < ind; i++)
    {
        if (nodeName == visited[i])
            return 1;
    }

    return 0;
}

//nodeName 찾아서 지우는 함수
void Graph::findEraseOne(Node* haveToVisit, int* nodeInd, int* prev, int weight, string nodeName)
{

    int find = 0;

    for (int i = 0; i < (*nodeInd); i++)
    {
        if (haveToVisit[i].vertexName == nodeName && haveToVisit[i].NodeWeight == weight)
        {
            find = i;
            break;
        }
    }

    if (find == (*nodeInd) - 1)
    {
        haveToVisit[find].vertexName = "";
        haveToVisit[find].NodeWeight = NULL;
        (*nodeInd)--;
        return;
    }

    for (int i = find; i < (*nodeInd) - 1; i++)
    {
        if (i == (*nodeInd) - 1)
            continue;

        prev[i] = prev[i + 1];
        haveToVisit[i] = haveToVisit[i + 1];
    }

    find = (*nodeInd) - 1;
    haveToVisit[find].vertexName = "";
    haveToVisit[find].NodeWeight = NULL;
    (*nodeInd)--;
    return;
}

//nodename 모두 지우는 함수
void Graph::findEraseAll(Node* haveToVisit, int* nodeInd, int* prev, string nodeName)
{
    bool whether = true;

    while (whether)
    {
        int find = 0;

        for (int i = 0; i < (*nodeInd); i++)
        {
            if (haveToVisit[i].vertexName == nodeName)
            {
                find = i;
                break;
            }
        }

        if (find == (*nodeInd) - 1)
        {
            haveToVisit[find].vertexName = "";
            haveToVisit[find].NodeWeight = NULL;

            whether = false;
        }

        else
        {
            for (int i = find; i < (*nodeInd) - 2; i++)
            {
                haveToVisit[i] = haveToVisit[i + 1];
                prev[i] = prev[i + 1];
            }
        }

        (*nodeInd) = (*nodeInd) - 1;
    }

    return;
}

//target에 해당하는 길이 없을 때 bool 함수
bool Graph::noWay(int target)
{
    int cnt = 0;
    Node* temp = GraphNodeList.NList[target]->adj;

    while (temp != NULL)
    {
        cnt++;
        temp = temp->adj;
    }

    temp = GraphNodeList.NList[target]->adj;
    int canGo = 0, cannot = 0;

    while (temp != NULL)
    {
        int index = findNode(temp->vertexName);

        if (GraphNodeList.NList[index]->isMarked == 0)
            canGo++;

        else
            cannot++;

        temp = temp->adj;
    }

    if (cannot != cnt)
        return false;

    else
        return true;
}

//Edge list 초기화 함수
void Graph::initEList(Edge* EList, int* eInd, int nodeNumber)
{
    int ind = (*eInd);

    for (int i = 0; i < nodeNumber; i++)
    {
        Node* temp = GraphNodeList.NList[i]->adj;
        string fromN = GraphNodeList.NList[i]->vertexName;

        while (temp)
        {
            int One = 0;
            for (int i = 0; i < *eInd; i++)
            {
                if (EList[i].from == temp->vertexName && EList[i].to == fromN)
                    One = 1;
            }

            if (One)
            {
                temp = temp->adj;
                continue;
            }

            if ((*eInd) == 0)
            {
                EList[ind].from = fromN;
                EList[ind].to = temp->vertexName;
                EList[ind].weight = temp->NodeWeight;
            }

            if ((*eInd) != 0)
            {
                Edge buffer;
                buffer.from = fromN;
                buffer.to = temp->vertexName;
                buffer.weight = temp->NodeWeight;

                int ins = -100;

                for (int i = 0; i < (*eInd); i++)
                {
                    if (EList[i].weight < buffer.weight)
                        continue;

                    else
                    {
                        if (EList[i].weight == buffer.weight && EList[i].from < fromN)
                            ins = i + 1;

                        else
                            ins = i;

                        break;
                    }
                }

                if (ins < 0)
                    ins = (*eInd);


                for (int i = (*eInd); i > ins; i--)
                {
                    EList[i] = EList[i - 1];
                }

                EList[ins] = buffer;
            }

            (*eInd)++;

            temp = temp->adj;
        }
    }
}

//nodename에 해당하는 parent를 반환한다.
int Graph::whoIs(int* parent, string nodeName)
{
    int n = findNode(nodeName);

    if (parent[n] == n) 
        return n;

    string Nodename = GraphNodeList.NList[parent[n]]->vertexName;

    return parent[n] = whoIs(parent, Nodename); 
}

//queue의 enqueue 기능이다.
void Graph:: enqueue(QUEUE* q, Node* temp) {

    Node* temp2 = new Node;
    temp2->vertexName = temp->vertexName;
    temp2->isMarked = temp->isMarked;
    temp2->NodeWeight = temp->NodeWeight;
    temp2->next = NULL;
    if (temp->adj != NULL) {
        temp2->adj = temp->adj;
    }


    if (!temp2)
        return;
    if (q->front == NULL) {
        q->front = temp2;
        q->rear = temp2;
        q->count++;
        return;
    }
    else {
        q->rear->next = temp2;
        q->rear = q->rear->next;
        q->count++;
        return;
    }
};

//queue의 dequeue 기능이다.
void Graph::dequeue(QUEUE* q, Node* dataout) {

    Node* temp;

    if (q->front == NULL) return;
    
    *dataout = *(q->front);
    temp = q->front;

    if (q->count == 1)
        q->rear = q->front = NULL;
    else
        q->front = q->front->next;
    (q->count)--;

    return;
};
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


//DFS 함수이다.
string Graph::DFS() {
    /////////////////////////////////////////////////////////
   //////////  TODO: Implement From Here      //////////////
    string visited[NodeMaxCount];
    string answer = "";

    int Remain = 0;
    int check_ind = 0;
    int t = 0;

    for (int i = 0; i < GraphNodeList.NodeNumber; i++) {

        Remain = 0;
        for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        {
            if (GraphNodeList.NList[i]->isMarked)
                continue;
            else
                Remain = 1;
        }

        if (i==0 || Remain) {
            t = findMin(visited, check_ind);
            DFS2(&answer, t, visited, &check_ind);
            answer += '\n';
        }
    }

    answer.pop_back();
    return answer;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

//BFS 함수이다.
string Graph::BFS() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    string* answer = new string;
    *answer = "";
    QUEUE queue;
    queue.count = 0;
    queue.front = NULL;
    queue.rear = NULL;

    int visit_ind = 0;
    Node* temp = NULL;
    int i = 0;
    string min = "FFFFFFFFFFFFFFFFFF";
    int index = 0;
    int visited[NodeMaxCount] = { 0 };
    Node* adj[NodeMaxCount];


    //남아있는지
    int sum = 0;
    for (int i = 0; i < GraphNodeList.NodeNumber; i++) {
        sum += visited[i];
    }

    while (GraphNodeList.NodeNumber != sum){
    //FindMin
     min = "FFFFFFFFFFFFFFFFFF";
    for (int i = 0; i < GraphNodeList.NodeNumber; i++) {
        
        if (GraphNodeList.NList[i]->vertexName < min && visited[findNode(GraphNodeList.NList[i]->vertexName)] == 0) {
            min = GraphNodeList.NList[i]->vertexName;
            index = i;
        }
    }

    //첫 노드 enqueue
        Node* node = GraphNodeList.NList[index];
        enqueue(&queue, node);
        visited[findNode(node->vertexName)] = 1;



        while (queue.front!= NULL){
            dequeue(&queue, node);
            (*answer).append(node->vertexName);
            (*answer).append(" ");
            node = GraphNodeList.NList[findNode(node->vertexName)];
            //모든 adj가 visit일때 check
            int check = 0;
            temp = node;
            while (temp->adj != NULL) {
                temp = temp->adj;
                if(visited[findNode(temp->vertexName)] == 0)
                    check++;

            }

            //adj 중 작은거부터 enqueue
                int i = 0;
                temp = node;
                
                //clear
                for (int i = 0; i < NodeMaxCount; i++)
                    adj[i] = NULL;

                while (temp->adj != NULL) {
                    temp = temp->adj;
                    adj[i] = temp;
                    i++;
                }

                //sort
                for (int j = 0; j < i; j++) {
                    for (int k = 0; k < i; k++) {
                        if (adj[j] < adj[k]) {
                            Node* temp2 = adj[j];
                            adj[j] = adj[k];
                            adj[k] = temp2;
                        }

                    }
                }

                //enqueue
                for (int j = 0; j < i; j++) {
                    if (visited[findNode(adj[j]->vertexName)] == 0) {
                        enqueue(&queue, GraphNodeList.NList[findNode(adj[j]->vertexName)]);
                        visited[findNode(adj[j]->vertexName)] = 1;
                    }
                }
           

        }

        //남아있는지
        sum = 0;
        for (int i = 0; i < GraphNodeList.NodeNumber; i++) {
            sum += visited[i];
        }

    }

    (*answer).pop_back();

    return *answer;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}


int Graph::addDirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}


int Graph::addUndirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
      //////////  TODO: Implement From Here      //////////////
    int ind = GraphNodeList.NodeNumber;


    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->adj = NULL;

    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->adj = NULL;

    //처음 노드일때
    if (ind == 0)
    {
        GraphNodeList.NList[ind] = new Node;
        GraphNodeList.NList[ind]->vertexName = nodeA;
        GraphNodeList.NList[ind]->isMarked = 0;

        GraphNodeList.NList[ind + 1] = new Node;
        GraphNodeList.NList[ind + 1]->vertexName = nodeB;
        GraphNodeList.NList[ind + 1]->isMarked = 0;

        GraphNodeList.NList[ind]->adj = newNodeB;
        GraphNodeList.NList[ind + 1]->adj = newNodeA;

        GraphNodeList.NodeNumber += 2;

        return true;
    }

    else
    {
        int alreadyA = -1;
        int alreadyB = -1;

        //이미 존재하는지 여부 찾기
        for (int i = 0; i < GraphNodeList.NodeNumber; i++) {
            if (GraphNodeList.NList[i]->vertexName == nodeA) {
                alreadyA = i;
            }
            if (GraphNodeList.NList[i]->vertexName == nodeB) {
                alreadyB = i;
            }
        }

        if (alreadyA == -1 && alreadyB == -1)
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = 0;

            GraphNodeList.NList[ind + 1] = new Node;
            GraphNodeList.NList[ind + 1]->vertexName = nodeB;
            GraphNodeList.NList[ind + 1]->isMarked = 0;

            ind++;
            ind = GraphNodeList.NodeNumber;

            GraphNodeList.NList[ind]->adj = newNodeB;
            GraphNodeList.NList[ind + 1]->adj = newNodeA;

            GraphNodeList.NodeNumber += 2;
        }


        if (alreadyA != -1 && alreadyB != -1)
        {

            Node* lastA = GraphNodeList.NList[alreadyA];

            while (lastA->adj != NULL)
            {
                lastA = lastA->adj;
            }


            Node* lastB = GraphNodeList.NList[alreadyB];

            while (lastB->adj != NULL)
            {
                lastB = lastB->adj;
            }

            lastA->adj = newNodeB;
            lastB->adj = newNodeA;
        }

        if (alreadyA != -1 && alreadyB == -1)
        {

            Node* last = GraphNodeList.NList[alreadyA];

            while (last->adj != NULL)
            {
                last = last->adj;
            }

            last->adj = newNodeB;

            ind = GraphNodeList.NodeNumber;


            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = 0;

            GraphNodeList.NList[ind]->adj = newNodeA;

            GraphNodeList.NodeNumber++;
        }

        if (alreadyA == -1 && alreadyB != -1)
        {

            Node* last = GraphNodeList.NList[alreadyB];

            while (last->adj != NULL)
            {
                last = last->adj;
            }

            last->adj = newNodeA;

            ind = GraphNodeList.NodeNumber;


            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = 0;

            GraphNodeList.NList[ind]->adj = newNodeB;

            GraphNodeList.NodeNumber++;
        }


        return 1;
    }

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int ind = GraphNodeList.NodeNumber;

    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->NodeWeight = weight;
    newNodeA->adj = NULL;


    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->NodeWeight = weight;
    newNodeB->adj = NULL;

    //처음 노드일때
    if (ind == 0)
    {
        if (nodeA > nodeB)
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->isMarked = 0;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->adj = newNodeA;

            GraphNodeList.NList[ind + 1] = new Node;
            GraphNodeList.NList[ind + 1]->isMarked = 0;
            GraphNodeList.NList[ind + 1]->vertexName = nodeA;
            GraphNodeList.NList[ind + 1]->adj = newNodeB;
        }

        else
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->isMarked = 0;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->adj = newNodeB;

            GraphNodeList.NList[ind + 1] = new Node;
            GraphNodeList.NList[ind + 1]->isMarked = 0;
            GraphNodeList.NList[ind + 1]->vertexName = nodeB;
            GraphNodeList.NList[ind + 1]->adj = newNodeA;
        }

        GraphNodeList.NodeNumber += 2;

        return true;
    }

    else
    {
        int alreadyA = -1;
        int alreadyB = -1;

        //이미 존재하는지 여부 찾기
        for (int i = 0; i < GraphNodeList.NodeNumber; i++) {
            if (GraphNodeList.NList[i]->vertexName == nodeA) {
                alreadyA = i;
            }
            if (GraphNodeList.NList[i]->vertexName == nodeB) {
                alreadyB = i;
            }
        }

        if (alreadyA !=-1 && alreadyB == -1)
        {

            Node* last = GraphNodeList.NList[alreadyA];

            while (last->adj != NULL)
            {
                if (last->adj->vertexName < nodeB)
                {
                    last = last->adj;
 
                }
                else
                {
                    break;
                }
            }

            newNodeB->adj = last->adj;
            last->adj = newNodeB;

            ind = GraphNodeList.NodeNumber;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = 0;
            GraphNodeList.NList[ind]->adj = newNodeA;

            GraphNodeList.NodeNumber++;
        }

        if (alreadyA == -1 && alreadyB != -1)
        {
            Node* last = GraphNodeList.NList[alreadyB];

            while (last->adj != NULL)
            {
                if (last->adj->vertexName < nodeA)
                {
                    last = last->adj;
                }
                else
                {
                    break;
                }
            }

            newNodeA->adj = last->adj;
            last->adj = newNodeA;

            ind = GraphNodeList.NodeNumber;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = 0;
            GraphNodeList.NList[ind]->adj = newNodeB;

            GraphNodeList.NodeNumber++;
        }

        if (alreadyA != -1 && alreadyB != -1)
        {

            Node* lastA = GraphNodeList.NList[alreadyA];

            while (lastA->adj != NULL)
            {
                if (lastA->adj->vertexName < nodeB)
                {
                    lastA = lastA->adj;
                }
                else
                {
                    break;
                }
            }

            newNodeB->adj = lastA->adj;
            lastA->adj = newNodeB;


            Node* lastB = GraphNodeList.NList[alreadyB];

            while (lastB->adj != NULL)
            {
                if (lastB->adj->vertexName < nodeB)
                {
                    lastB = lastB->adj;
                }
                else
                {
                    break;
                }
            }

            newNodeA->adj = lastB->adj;
            lastB->adj = newNodeA;
        }

        if (alreadyA == -1 && alreadyB == -1)
        {
            ind = GraphNodeList.NodeNumber;

            if (nodeA < nodeB)
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeA;
                GraphNodeList.NList[ind]->isMarked = 0;
                GraphNodeList.NList[ind]->adj = newNodeB;

                GraphNodeList.NList[ind + 1] = new Node;
                GraphNodeList.NList[ind + 1]->vertexName = nodeB;
                GraphNodeList.NList[ind + 1]->isMarked = 0;
                GraphNodeList.NList[ind + 1]->adj = newNodeA;

                ind++;
                ind = GraphNodeList.NodeNumber;
            }

            else
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeB;
                GraphNodeList.NList[ind]->isMarked = 0;

                GraphNodeList.NList[ind + 1] = new Node;
                GraphNodeList.NList[ind + 1]->vertexName = nodeA;
                GraphNodeList.NList[ind + 1]->isMarked = 0;

                ind++;
                ind = GraphNodeList.NodeNumber + 1;
            }

            GraphNodeList.NList[ind]->adj = newNodeB;

            GraphNodeList.NodeNumber += 2;
        }

        int targetInd = GraphNodeList.NodeNumber - 1;

        for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        {
            if (GraphNodeList.NList[i]->vertexName < GraphNodeList.NList[targetInd]->vertexName)
                continue;

            if (targetInd == i)
                continue;

            else
            {
                Node* tempNode = GraphNodeList.NList[i];

                GraphNodeList.NList[i] = GraphNodeList.NList[targetInd];
                GraphNodeList.NList[targetInd] = tempNode;
            }
        }
        return 1;
    }

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::countUndirectedCycle() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int answer2 = 0;


    for (int k = 0; k < GraphNodeList.NodeNumber; k++) {

        string answer;
        string visited[NodeMaxCount];

        int check_ind = 0;
        int t = 0;

        Node* node = GraphNodeList.NList[k];

        DFS2(&answer, k, visited, &check_ind);
        answer.pop_back();

        for (int i = 4; i < GraphNodeList.NodeNumber * 2; i += 2) {

            Node* temp = GraphNodeList.NList[findNode(answer.substr(i, 1))];

            while (temp->adj != NULL) {
                temp = temp->adj;
                if (temp->vertexName == node->vertexName)
                    answer2++;
            }

        }

    }

    //3,4 cycle만 고려하였다.
    if (answer2 % 3 == 0)
        return answer2 / 3;
    if (answer2 % 3 == 1)
        return 1 + (answer2 - 4) / 3;
    if (answer2 % 3 == 2)
        return 2 + (answer2 - 8) / 3;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getTopologicalSort() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return "";
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::countDirectedCycle() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getShortestPath(string source, string destination) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return "";
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getAllShortestPaths() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////   

    return "";
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream& fout, string startNode) {
    /////////////////////////////////////////////////////////
   //////////  TODO: Implement From Here      //////////////
    string visited[NodeMaxCount];
    int prev[NodeMaxCount];

    Node haveToVisit[NodeMaxCount];

    int visitInd = 0;
    int nodeInd = 0;

    int nodeNumber;
    nodeNumber = GraphNodeList.NodeNumber;
    int dist = 0;
    int cnt = 0;


    string answer = "";

    int start = findNode(startNode);
    int target = 0;
    int parent = 0;



    while (cnt != nodeNumber - 1)
    {
        if (cnt == 0)
            target = start;

        GraphNodeList.NList[target]->isMarked = 1;
        visited[visitInd] = GraphNodeList.NList[target]->vertexName;
        visitInd++;

        if (noWay(target))
        {
            target = parent;
            continue;
        }


        answer.append(GraphNodeList.NList[target]->vertexName);
        answer.append(" ");


        Node* temp = GraphNodeList.NList[target]->adj;

        if (temp == NULL)
        {
            target = parent;
            continue;
        }

        while (temp != NULL)
        {

            //가지고 있는지 없는지
            int have = 0;

            for (int i = 0; i < nodeInd; i++)
            {
                int listNode = findNode(haveToVisit[i].vertexName);


                if (listNode == target && !GraphNodeList.NList[listNode]->isMarked)
                {
                    int a = prev[i];
                    string cmp = GraphNodeList.NList[a]->vertexName;

                    if (cmp == temp->vertexName)
                        have = 1;
                }
            }

            if (!have)
            {
                int index = findNode(temp->vertexName);
                if (!GraphNodeList.NList[index]->isMarked)
                {
                    haveToVisit[nodeInd].vertexName = temp->vertexName;
                    haveToVisit[nodeInd].NodeWeight = temp->NodeWeight;
                    prev[nodeInd] = target;
                    nodeInd++;
                }
            }

            temp = temp->adj;
        }


        bool whether = 0;
        string nodeName = "";
        int minDis = INF, minNode = 0, weight = 0;

        while (whether == 0)
        {
            for (int i = 0; i < nodeInd; i++)
            {
                if (haveToVisit[i].NodeWeight < minDis)
                {
                    nodeName = haveToVisit[i].vertexName;
                    minDis = haveToVisit[i].NodeWeight;
                    weight = haveToVisit[i].NodeWeight;
                    parent = prev[i];
                    minNode = findNode(nodeName);

                }
            }

            target = minNode;

            if (GraphNodeList.NList[target]->isMarked == 1)
                findEraseOne(haveToVisit, &nodeInd, prev, weight, nodeName);
            else
                whether = 1;
        }

        findEraseAll(haveToVisit, &nodeInd, prev, nodeName);
        answer.append(GraphNodeList.NList[target]->vertexName);
        answer.append(" ");
        answer.append(to_string(minDis));

        fout << answer << endl;

        answer.clear();
        dist += minDis;
        cnt++;
    }

    return dist;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream& fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int edgeNum = 0;
    int nodeNumber = GraphNodeList.NodeNumber;

    for (int i = 0; i < nodeNumber; i++)
    {
        Node* temp = GraphNodeList.NList[i]->adj;
        while (temp != NULL)
        {
            edgeNum++;
            temp = temp->adj;
        }
    }

    edgeNum /= 2;

    int eInd = 0;
    Edge* EList = new Edge[edgeNum];


    initEList(EList, &eInd, nodeNumber);

    int dist = 0;
    string answer = "";

    int* parent = new int[nodeNumber];
    for (int i = 0; i < nodeNumber; i++)
        parent[i] = i;

    for (int i = 0; i < edgeNum; i++)
    {
        int same = 0;
        int f = whoIs(parent, EList[i].from);
        int t = whoIs(parent, EList[i].to);

        if (f == t)
            same = 1;

        //parent가 같지 않다면
        if (!same)
        {
            dist += EList[i].weight;
            answer = answer + EList[i].from + " " + EList[i].to + " " + to_string(EList[i].weight);
            fout << answer << endl;

            answer = "";

            if (f < t)
                parent[t] = f;
            if (f > t)
                parent[f] = t;
        }
    }

    return dist;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}