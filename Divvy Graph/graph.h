
/*graph.h*/

//Patrick Welch
//welch9
//CS251
//Due: 4/18/2017

#pragma once

#include <string>
#include <vector>
#include <set>


//#include "graph.cpp"

using namespace std;


class Graph
{
private:
    class Edge
    {
    public:
        int   Src, Dest, Weight;
        Edge *Next;
    };

    Edge  **Vertices;
    string *Names;
    int     NumVertices;
    int     NumEdges;
    int     Capacity;

public:
    Graph(int N);
    ~Graph();


    int GetNumVertices();
    int GetNumEdges();
    bool AddVertex(string v);

    void UpdateWeight(string src, string dest);
    bool EdgeExists(string src, string dest);

    int GetNumNeighbors(string v);
    int SumEdgeWeights(string v);

    //Edge *Graph::FindEdge(string src, string dest);

    int GetOneWeight(int src, int dest);

    bool AddEdge(string src, string dest, int weight);
    set<string> GetVertices();
    set<string> GetNeighbors(string v);
    vector<int> GetEdgeWeights(string src, string dest);
    vector<int> GetIntNeighbors(int v);
    int FindVertexByName(string v);
    vector<string> BFS(string v);

    void PrintGraph(string title);
};
