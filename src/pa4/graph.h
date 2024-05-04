#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647 
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

struct Node 
{
    string vertexName = "";
    int isMarked = 0;
    int NodeWeight = 0;
    Node* adj = NULL;
    Node* next = NULL; //for queue
};

struct NodeList 
{
    int NodeNumber = 0;
    Node* NList[NodeMaxCount];
};

struct QUEUE {

    int count;
    Node* front;
    Node* rear;
};

struct Edge
{
    string from;
    string to;
    int weight;
};



///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
    Graph() { };
    ~Graph() { };

    string DFS();
    string BFS();

    int addDirectedEdge(string nodeA, string nodeB);
    int addDirectedEdge(string nodeA, string nodeB, int weight);
    int addUndirectedEdge(string nodeA, string nodeB);
    int addUndirectedEdge(string nodeA, string nodeB, int weight);

    int countUndirectedCycle();
    string getTopologicalSort();
    int countDirectedCycle();
    string getShortestPath(string source, string destination);
    string getAllShortestPaths();
    int primMST(ofstream&, string startNode);
    int kruskalMST(ofstream&);


private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    //FOR LIST
    NodeList GraphNodeList;

    int findMin(string* visited, int ind);
    string findMin(string nodeName, string* visited, int ind);
    int findNode(string nodeName);
    bool isVisited(string nodeName, string* visited, int ind);
    void DFS2(string* answer, int t, string* visited, int* visitInd);
    void enqueue(QUEUE* q, Node* temp);
    void dequeue(QUEUE* q, Node* dataout);
    void DFS2_cycle(string* answer, int t, string* visited, int* visitInd);
    void findEraseOne(Node* haveToVisit, int* nodeInd, int* prev, int weight, string nodeName);
    void findEraseAll(Node* haveToVisit, int* nodeInd, int* prev, string nodeName);
    bool noWay(int target);
    void initEList(Edge* EList, int* eInd, int nodeNumber);
    int whoIs(int* parent, string nodeName);


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};