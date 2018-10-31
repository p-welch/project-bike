Patrick Welch

Divvy Graph Analysis

This program accepts two filenames, a csv of station names and a csv of trip records linked by station ID.
Once this data is compiled into a graph, the program then implements the following functionallity:

1. info about a station:
The “info” command provides info about a station. The user inputs a station id, and the program outputs: 
 
• Name 
• Position 
• Capacity 
• # of adjacent stations in the graph 
• Total # of trips to those adjacent stations 
• A list of each adjacent station (name and id) with # of trips to that station 
 

2. # of trips between 2 stations 

Given the starting station id and the destination station id, reports the # of trips taken from the starting 
station to the destination station. This is simply the weight on the edge from the starting station’s vertex 
to the destination station’s vertex.
 
3. breadth-first search (bfs) from a station 

The “bfs” command performs a breadth-first search, starting from the given station id.  The returned vector 
is then output to the screen in order. 

4. debug 

This command calls up the graph classes' PrintGraph functinoality.

5. exit 
Exits program