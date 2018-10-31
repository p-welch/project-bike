/*main.cpp*/

//Patrick Welch
//welch9
//CS251
//Due: 4/18/2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "graph.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS  // ignore C-related security warnings in Visual Studio:


//
// Defines a Divvy Station:

class Station
{
public:
  string Name;
  int    ID;
  double Latitude;
  double Longitude;
  int    Capacity;

  Station(string name, int id, double latitude, double longitude, int capacity)
  {
    Name = name;
    ID = id;
    Latitude = latitude;
    Longitude = longitude;
    Capacity = capacity;
  }

    string getStationName()
  {
    return Name;
  }
};



vector<int> TurnNamesIntoID(vector<string> stringBFS, vector<Station> stationVector)
{
    vector<int> bfsID;
    for (auto x : stringBFS)
    {
        for (auto v : stationVector)

            if (v.Name == x){
                bfsID.push_back(v.ID);
            }
    }
    return bfsID;
}


//Performs BFS command
void BfsCommand(int fromID, vector<Station> stations, Graph& G)
{
    Station *infoBlock;
    int checkInfo = 0;
    for (auto v : stations){
        if (v.ID == fromID)
        {
          infoBlock = &v;
          checkInfo = 1;
          break;
        }
    }

    if (checkInfo){
        vector<string> bfsNames;
        vector<int> bfsID;
        bfsNames = G.BFS(infoBlock->Name);
        bfsID = TurnNamesIntoID(bfsNames, stations);

        cout << "# of stations: " << bfsNames.size() << endl;
        for (auto b : bfsID){
            cout << b << ", ";

        }
        cout << "#" << endl;
    }

    else{
        cout << "** No such station..."<< endl;
    }

}


//Performs trip command
void TripsCommand(int fromID, int toID, vector<Station> stations, Graph& G)
{

    int indexSrc = -1;
    int indexDest = -1;

    for (auto v : stations){
      if (v.ID == fromID)
      {
        indexSrc = G.FindVertexByName(v.Name);
      }
      if (v.ID == toID){
        indexDest = G.FindVertexByName(v.Name);
      }
    }

    if (indexSrc != -1 && indexDest != -1){
        cout << stations[indexSrc].Name << " -> " << stations[indexDest].Name << endl;
        cout << "# of trips: " << G.GetOneWeight(indexSrc, indexDest) << endl;
    }
    else {
        cout << "** One of those stations doesn't exist..." << endl;
    }

}


//print function for neighbors
void PrintNeighborsSorted(string v, vector<Station> s, Graph& G)
{

    int indexSrc = G.FindVertexByName(v);
    if (indexSrc == -1)
      return;
    int indexDest = 0;
    set<string> neighbors = G.GetNeighbors(v);
    for (string n : neighbors)
    {
        cout << "   " << n << " (";
        indexDest = G.FindVertexByName(n);
        cout << s[indexDest].ID << "): ";
        cout << G.GetOneWeight(indexSrc, indexDest) << endl;

    }

}


//Info command function
void InfoCommand(vector<Station> stations, int fromID, Graph& G)
{
    //Station *infoBlock;
    string tempString;


    int checkInfo = 0;
    for (auto v : stations){
      if (v.ID == fromID)
      {
          //infoBlock = &v;
          tempString = v.Name;
          checkInfo = 1;
          break;
      }

    }

    int indexS = G.FindVertexByName(tempString);


    //if (checkInfo)
    if (checkInfo && indexS != -1)
    {
        //cout << infoBlock->Name <<endl;
        cout << stations[indexS].Name <<endl;

        //cout << "(" << infoBlock->Latitude << "," << infoBlock->Longitude << ")" << endl;
        cout << "(" << stations[indexS].Latitude << "," << stations[indexS].Longitude << ")" << endl;

        //cout << "Capacity: " << infoBlock->Capacity << endl;
        cout << "Capacity: " << stations[indexS].Capacity << endl;

        //cout << "# of destination stations:    " << G.GetNumNeighbors(infoBlock->Name)  << endl;
        cout << "# of destination stations:    " << G.GetNumNeighbors(stations[indexS].Name)  << endl;

        //cout << "# of trips to those stations: " << G.SumEdgeWeights(infoBlock->Name) << endl;
        cout << "# of trips to those stations: " << G.SumEdgeWeights(stations[indexS].Name) << endl;

        cout << "Station: trips" << endl;

        //PrintNeighborsSorted(infoBlock->Name, stations, G);
        //int indexSrc = G.FindVertexByName(infoBlock->Name);
        int indexSrc = G.FindVertexByName(stations[indexS].Name);

        if (indexSrc == -1)
          return;
        int indexDest = 0;
        //set<string> neighbors = G.GetNeighbors(infoBlock->Name);
        set<string> neighbors = G.GetNeighbors(stations[indexS].Name);
        for (string n : neighbors)
        {
            cout << "   " << n << " (";
            indexDest = G.FindVertexByName(n);
            cout << stations[indexDest].ID << "): ";
            cout << G.GetOneWeight(indexSrc, indexDest) << endl;

        }
    }

    else {
        cout << "** No such station..."<< endl;
    }

}


//Unused, creates a sorted station vector
vector<Station> SortAlphabetical(vector<Station> s)
{

      sort( s.begin(), s.end(),
        [ ](Station s1, Station s2)  // lambda expression:
        {
           if (s1.getStationName() < s2.getStationName())
              return true;
            else
              return false;
        } );

    return s;
}



//
// Inputs the stations from the given file, adding each station name as a
// vertex to the graph, and storing a new Station object into the vector.
// The graph is passed by reference --- note the & --- so that the changes
// made by the function are returned back.  The vector of Station objects is
// returned by the function.
//
vector<Station> InputStations(Graph& G, string filename)
{
  string line;
  vector<Station> V;

  ifstream input(filename);
  if (!input.good())  // failed to open:
    return V;

  getline(input, line);  // skip first line: column headers
  getline(input, line);  // first line of real data

  while (!input.eof())  // for each line of input:
  {
    stringstream  ss(line);

    // format:
    //   id,name,latitude,longitude,dpcapacity,online_date
    //   456,2112 W Peterson Ave,41.991178,-87.683593,15,5/12/2015
    //   101,63rd St Beach,41.78101637,-87.57611976,23,4/20/2015
    //
    string  stationID, name, latitude, longitude, capacity;

    //
    // parse the line:
    //
    getline(ss, stationID, ',');
    getline(ss, name, ',');
    getline(ss, latitude, ',');
    getline(ss, longitude, ',');
    getline(ss, capacity, ',');

    //
    // Create a new station object:
    //
    Station S(name,
    stoi(stationID),
    stod(latitude),
    stod(longitude),
    stoi(capacity));

    V.push_back(S);
    G.AddVertex(S.Name);

    getline(input, line);
  }
  return V;
}

//vector.count

//
// Inputs the trips, adding / updating the edges in the graph.  The graph is
// passed by reference --- note the & --- so that the changes made by the
// function are returned back.  The vector of stations is needed so that
// station ids can be mapped to names; it is passed by reference only for
// efficiency (so that a copy is not made).
//
void ProcessTrips(string filename, Graph& G, vector<Station>& stations)
{
  string line;
  int checkSrc = 0;
  int checkDest = 0;

  ifstream input(filename);
  if (!input.good())  // failed to open:
    return;

  getline(input, line);  // skip first line: column headers
  getline(input, line);  // first line of real data

  while (!input.eof())  // for each line of input:
  {
    stringstream  ss(line);

    // format:
    //   trip_id,starttime,stoptime,bikeid,tripduration,from_station_id,from_station_name,to_station_id,to_station_name,usertype,gender,birthyear
    //   10426561,6/30/2016 23:35,7/1/2016 0:02,5229,1620,329,Lake Shore Dr & Diversey Pkwy,307,Southport Ave & Clybourn Ave,Subscriber,Male,1968
    //
    string  tripID, fromID, toID, skip;

    //
    // parse the input line:
    //
    getline(ss, tripID, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, fromID, ',');
    getline(ss, skip, ',');
    getline(ss, toID, ',');
    getline(ss, skip, ',');

    //
    // NOTE: don't trust the names in the trips file, not always accurate.  Trust the
    // from and to station ids, and then lookup in our vector of stations:
    //
    checkSrc = 0;
    checkDest = 0;
    string stationSrc;
    string stationDest;

    int numFromID = stoi(fromID);
    int numToID = stoi(toID);

    for ( auto v: stations)
    {
        if (numFromID == v.ID){
            checkSrc = 1;
            stationSrc = v.Name;
        }
        if (numToID == v.ID){
            checkDest = 1;
            stationDest = v.Name;
        }
    }

    //
    // TODO:
    if (checkSrc && checkDest){
        if (G.EdgeExists(stationSrc, stationDest)){
            G.UpdateWeight(stationSrc, stationDest);
        }
        else {
            G.AddEdge(stationSrc, stationDest, 1);
        }
        //  - add new edge or update existing edge for this trip
        //
    }


    getline(input, line);

    }

}


//
// getFileName:
//
// Inputs a filename from the keyboard, checks that the file can be
// opened, and returns the filename if so.  If the file cannot be
// opened, an error message is output and the program is exited.
//
string getFileName()
{
  string filename;

  // input filename from the keyboard:
  getline(cin, filename);

  // make sure filename exists and can be opened:
  ifstream file(filename);
  if (!file.good())
  {
    cout << "**Error: unable to open '" << filename << "'" << endl << endl;
    std::terminate();
  }

  return filename;
}


int main()
{
  int    N = 1000;
  Graph  DivvyGraph(N);

  cout << "** Divvy Graph Analysis **" << endl;

  string stationsFilename = getFileName();
  string tripsFilename = getFileName();

  vector<Station> stations = InputStations(DivvyGraph, stationsFilename);
  //vector<Station> sortedStations = SortAlphabetical(stations);

  ProcessTrips(tripsFilename, DivvyGraph, stations);

  //DEBUG
//        cout << "DEBUG" << endl;
//  for (auto i : stations)
//  {
//      cout << "Name:" << i.Name << endl;
//
//
//  }
  cout << ">> Graph:" << endl;
  cout << "   # of vertices: " << DivvyGraph.GetNumVertices() << endl;
  cout << "   # of edges:    " << DivvyGraph.GetNumEdges() << endl;
  cout << ">> Ready:" << endl;

  string cmd;
  int    fromID, toID;

  cout << ">> ";
  cin >> cmd;

  while (cmd != "exit")
  {
    if (cmd == "info")
    {
      cin >> fromID;
      InfoCommand(stations, fromID, DivvyGraph);
    }
    else if (cmd == "trips")
    {
      cin >> fromID;
      cin >> toID;
      TripsCommand(fromID, toID, stations, DivvyGraph);
    }
    else if (cmd == "bfs")
    {
      cin >> fromID;
      BfsCommand(fromID, stations, DivvyGraph);
    }
    else if (cmd == "debug")
    {
      DivvyGraph.PrintGraph("Divvy Graph");
    }
    else
    {
      cout << "**Invalid command, try again..." << endl;
    }

    cout << ">> ";
    cin >> cmd;
  }

  cout << "**Done**" << endl;
  return 0;
}
