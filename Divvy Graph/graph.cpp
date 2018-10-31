
/*graph.cpp*/

//Patrick Welch
//welch9
//CS251
//Due 4/18/2017

#include <iostream>
#include <set>
#include <queue>



#include "graph.h"

using namespace std;
//
// Constructor:
//
Graph::Graph(int N)
{
  this->NumVertices = 0;
  this->NumEdges = 0;
  this->Capacity = N;

  this->Vertices = new Edge*[N];
  this->Names = new string[N];

}


//
// Destructor:
//
Graph::~Graph()
{
  //
  // Future work:
  //
}




int Graph::GetNumVertices()
{

      return this->NumVertices;

}

int Graph::GetNumEdges()
{

      return this->NumEdges;

}


//Checks if edge exists
bool Graph::EdgeExists(string src, string dest)
{
    int indexSrc = FindVertexByName(src);
    int indexDest = FindVertexByName(dest);

    if (indexSrc < 0 || indexDest < 0){
        return false;
    }

    Edge * curr = this->Vertices[indexSrc];

    while (curr!= nullptr)
    {

        if (curr->Dest == indexDest){
            return true;
        }

        curr = curr->Next;
    }

    return false;

}


//updates weight on an edge
void Graph::UpdateWeight(string src, string dest)
{
    int indexSrc = FindVertexByName(src);
    int indexDest = FindVertexByName(dest);

    if (indexSrc < 0 || indexDest < 0){
        return;
    }

    Edge *curr = this->Vertices[indexSrc];

    while (curr!= nullptr)
    {

        if (curr->Dest == indexDest){
            curr->Weight = curr->Weight + 1;
            return;
        }

        curr = curr->Next;
    }

    return;

}

//cant get this to work
//Edge *Graph::FindEdge(string src, string dest)
//{
//    Edge *
//    int indexSrc = FindVertexByName(src);
//    int indexDest = FindVertexByName(dest);
//
//    if (indexSrc < 0 || indexDest < 0){
//        return false;
//    }
//
//
//
//}

//
// AddVertex:
//
// Adds the given vertex v to the graph, returning true if
// successful and false if not.  The add fails if (1) the
// graph is full, or (2) the vertex already exists in the
// graph.
//
bool Graph::AddVertex(string v)
//bool Graph::AddVertex(Station v)
{

   if (this->NumVertices >= this->Capacity){
      return false;
   }

   for (int i = 0; i < this->NumVertices; i++)
   {
      //if (this->Names[i]->Name == v.Name){
      if (this->Names[i] == v){
         return false;
      }
   }


   int i = this->NumVertices;

   this->Vertices[i] = nullptr;  // head of LL: null
   //this->Names[i].Name == v.Name;
   this->Names[i] = v;           // copy vertex string:

   this->NumVertices++;
   return true;
}


//
// AddEdge:
//
// Adds an edge from src to dest, with the given weight, returning
// true if successful and false if not.  The add fails if the src
// or dest vertex do not exist.
//
bool Graph::AddEdge(string src, string dest, int weight)
{

   int indexSrc = -1;
   int indexDest = -1;

   for (int i = 0; i < this->NumVertices; i++)
   {
      //printf(" i: %d name: %s, src: %s, dest: %s \n", i, this->Names[i], src, dest);
      //cout << " i: %d name: %s, src: %s, dest: %s \n", i, this->Names[i], src, dest;
      if (this->Names[i] == src)
      //if (this->Names[i].Name == src)
      {
         //printf(" src if trigger\n");
         indexSrc = i;
         //break;
      }
      if (this->Names[i] == dest)
      //if (this->Names[i].Name == dest)
      {
      //printf(" dest if trigger\n");
         indexDest = i;
         //break;
      }

   }

   if (indexSrc == -1){
            //cout << "fail src" << endl;
      return false;
   }

   if (indexDest == -1){
         //cout << "fail dest" << endl;
      return false;
   }

   //Traversal
   Edge *e = new Edge();
   e->Src = indexSrc;
   e->Dest = indexDest;
   e->Weight = weight;
   e->Next = nullptr;

   Edge *prev = nullptr;
   Edge *curr = Vertices[indexSrc];

   if (Vertices[indexSrc] == nullptr){
      this->Vertices[indexSrc] = e;
      this->NumEdges++;
      return true;
   }


   //while (curr!=nullptr && (curr->Dest <= e->Dest))
   while (curr!=nullptr)
   {

      if (curr->Dest > e->Dest)
      {
         break;

      }

      if ((curr->Dest == e->Dest) && (e->Weight <= curr->Weight))
      {
         break;
      }

      prev = curr;
      curr = curr->Next;
   }

   if (prev == nullptr)
   {
      this->Vertices[indexSrc] = e;
      e->Next = curr;
   }
   else if (curr == nullptr){
    prev->Next = e;
   }
   else{
      prev->Next = e;
      e->Next = curr;
   }


   this->NumEdges++;
   //cout << "success" << endl;
   return true;
}

//
// GetVertices:
//
// Returns a set containing all vertices in the graph.
//
set<string> Graph::GetVertices()
{
   set<string>  vertices;

   int i = 0;
   /*
   for (auto name : Names){
      vertices[i] = name;
      i++;
   }

   */

   for (i = 0; i < this->NumVertices; i++)
   {
      //vertices.insert(this->Names[i].Name);
      vertices.insert(this->Names[i]);
   }

   //
   // TODO:
   //

   return vertices;
}


//Returns the count of neighbors
int Graph::GetNumNeighbors(string v)
{
    //Edge *prev = nullptr;
    int countNeighbors = 0;
    int index = FindVertexByName(v);

    if (index == -1)
        return -1;

    Edge *curr = Vertices[index];
    while (curr != nullptr)
    {

        countNeighbors++;
        //prev = curr;
        curr = curr->Next;
    }

    return countNeighbors;


}
// Another attempt to make a find edge function
//Edge *Graph::FindEdge(string src, string dest)
//{
//    Edge *temp = nullptr;
//
//   int indexSrc = -1;
//   int indexDest = -1;
//
//   for (int i = 0; i < this->NumVertices; i++)
//   {
//      //printf(" i: %d name: %s, src: %s, dest: %s \n", i, this->Names[i], src, dest);
//      //cout << " i: %d name: %s, src: %s, dest: %s \n", i, this->Names[i], src, dest;
//      if (this->Names[i] == src)
//      //if (this->Names[i].Name == src)
//      {
//         //printf(" src if trigger\n");
//         indexSrc = i;
//         //break;
//      }
//      if (this->Names[i] == dest)
//      //if (this->Names[i].Name == dest)
//      {
//      //printf(" dest if trigger\n");
//         indexDest = i;
//         //break;
//      }
//
//   }
//
//   if (indexSrc == -1){
//            //cout << "fail src" << endl;
//      return temp;
//   }
//
//   if (indexDest == -1){
//         //cout << "fail dest" << endl;
//      return temp;
//   }
//
//         //Edge *prev = nullptr;
//      Edge *curr = Vertices[index];
//
//      while (curr != nullptr)
//      {
//         //if (curr->Dest
//       if (curr->Dest == indexDest){
//            temp = curr;
//            return temp;
//       }
//       //prev = curr;
//       curr = curr->Next;
//
//      }
//
//      return temp;
//
//
//
//
//}



//
// GetNeighbors:
//
// Returns a set containing all the vertices adjacent to v.
// If v does not exist in the graph, the returned set is
// empty.
//
set<string> Graph::GetNeighbors(string v)
{
  set<string>  neighbors;

   int i = 0;
   int index = -1;
   for (i = 0; i < this->NumVertices; i++){
      if (v == Names[i])
      //if (v == Names[i].Name)
      {
       index = i;
      }
   }

   if (index == -1){
      return neighbors;
   }

   else{
      //Edge *prev = nullptr;
      Edge *curr = Vertices[index];

      while (curr != nullptr)
      {
         //if (curr->Dest
       neighbors.insert(Names[curr->Dest]);
       //prev = curr;
       curr = curr->Next;

      }

      return neighbors;

   }

   //
   // TODO:
   //

  return neighbors;
}


//Returns neighbors as index numbers that reflects order of edges as inputted
vector<int> Graph::GetIntNeighbors(int v)
{
  vector<int>  neighbors;

      Edge *curr = Vertices[v];

      while (curr != nullptr)
      {
         //if (curr->Dest
       //neighbors.insert(Names[curr->Dest]);
       neighbors.push_back(curr->Dest);
       //prev = curr;
       curr = curr->Next;

      }
      return neighbors;

}


//return a single weight
int Graph::GetOneWeight(int src, int dest)
{


   if (src == -1){
            //cout << "fail src" << endl;
      return 0;
   }

   if (dest == -1){
         //cout << "fail dest" << endl;
      return 0;
   }

   Edge *curr = Vertices[src];
   while (curr!= nullptr)
   {

       if (curr->Dest == dest)
       {
           return curr->Weight;
       }
       curr = curr->Next;
   }

    return 0;


}


//
// GetEdgeWeights:
//
// Returns a vector containing all the weights for edges
// from src to dest.  The weights are in ascending order,
// and may contain duplicates (since it is legal for there
// to be 2 different edges from src to dest with the same
// weight).  If src or dest do not exist in the graph, the
// returned vector is empty.
//
vector<int> Graph::GetEdgeWeights(string src, string dest)
{
   vector<int> weights;

   int indexSrc = -1;
   int indexDest = -1;

   for (int i = 0; i < this->NumVertices; i++)
   {
      //printf(" i: %d name: %s, src: %s, dest: %s \n", i, this->Names[i], src, dest);
      //cout << " i: %d name: %s, src: %s, dest: %s \n", i, this->Names[i], src, dest;
      if (this->Names[i] == src)
      {
         //printf(" src if trigger\n");
         indexSrc = i;
         //break;
      }
      if (this->Names[i] == dest)
      {
      //printf(" dest if trigger\n");
         indexDest = i;
         //break;
      }

   }

   if (indexSrc == -1){
            //cout << "fail src" << endl;
      return weights;
   }

   if (indexDest == -1){
         //cout << "fail dest" << endl;
      return weights;
   }

   Edge *curr = Vertices[indexSrc];
   //int temp = curr->Dest;
   while (curr!=nullptr)
   {
    if (curr->Dest == indexDest){
       //temp = curr->Weight;
       //printf("debug match");
      weights.push_back(curr->Weight);
      //neighbors.insert(Names[curr->Dest]);
    }
      curr = curr->Next;
   }

   return weights;
}

//Returns sum of all weights on a vertex
int Graph::SumEdgeWeights(string v)
{

  int weightSum = 0;

  int index = FindVertexByName(v);
  if (index == -1)
    return -1;

  Edge *curr = Vertices[index];

  while (curr != nullptr)
  {
     //if (curr->Dest
   //neighbors.insert(Names[curr->Dest]);
   weightSum += curr->Weight;
   //prev = curr;
   curr = curr->Next;

  }
  return weightSum;

}

//
// PrintGraph:
//
// Prints the graph, typically for debugging purposes.
//
void Graph::PrintGraph(string title)
{
  cout << ">>Graph: " << title << endl;
  cout << "  # of vertices: " << this->NumVertices << endl;
  cout << "  # of edges:    " << this->NumEdges << endl;
  cout << "  Capacity:      " << this->Capacity << endl;

  cout << "  Vertices:" << endl;

  for (int v = 0; v < this->NumVertices; ++v)
  {
    cout << "    " << v << " (" << this->Names[v] << "): ";

    Edge *edge = this->Vertices[v];
    while (edge != nullptr)
    {
      cout << "(" << edge->Src << "," << edge->Dest << "," << edge->Weight << ")";

      edge = edge->Next;
      if (edge != nullptr)
        cout << ", ";
    }

    cout << endl;
  }
}


int Graph::FindVertexByName(string v)
{
   for (int i = 0; i < this->NumVertices; i++)
   {
     if (v == Names[i])
     {
        return i;
     }
   }

   return -1;


}


//
// BFS:
//
// Performs a breadth-first search starting from vertex v, returning
// a vector that denotes the order in vertices were visited.  If v
// does not exist in the graph, an empty vector is returned.
//
// NOTE that a vertex will appear at most once in the returned vector,
// since once a vertex is visited, it is never visited again.

vector<string> Graph::BFS(string v)
{
  vector<string>  visited;
  vector<int>     visitedInt;
  queue<int>      frontierQueue;
  set<int>        discoveredSet;

  //set<

  int currentV;

  int start = FindVertexByName(v);

  if (start < 0){
     return visited;
  }

  frontierQueue.push(start);
  discoveredSet.insert(start);
  int i = 0;
  //int val = 0;

  while (!(frontierQueue.empty())){
     i++;
     currentV = frontierQueue.front();
     frontierQueue.pop();

     visited.push_back(this->Names[currentV]);
     visitedInt.push_back(currentV);
     vector<int> V = GetIntNeighbors(currentV);

     for (int adjV: V)
     {
          if (discoveredSet.find(adjV) == discoveredSet.end())  // not found:
          //if (discoveredSet.count(adjV))
           {

             frontierQueue.push(adjV);
             discoveredSet.insert(adjV);
                 //}

           }

     }

  }

  return visited;
}

