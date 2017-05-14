/*
 * File name: ppathfinder.cpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#include <fstream>
#include <stack>
#include <queue>
#include "Vertex.hpp"
#include "ActorGraph.hpp"
#include "Edge.hpp"
#include "BFS.hpp"

using namespace std;

/*
 * Function name: printpath
 * This function takes in a stack of string representing the shortest path
 * and prints it out to the file in the given format
 */
void printpath (stack<string>& path, ofstream & out) {
  // strings to store the info
  string actor;
  string movie;
  string year;
  string connection;

  // get the starting actor
  actor = path.top();
  path.pop();

  // check if the path format is correct
  if (path.size() % 3 != 0) {
    cout << "incorrect size of path stack: " << path.size();
    cout << "should be a multiple of 3." <<endl;
    return;
  }
  out << "(" + actor +")";

  // printing each connections
  while(!path.empty()) {
    year = path.top();
    path.pop();
    movie = path.top();
    path.pop();
    actor = path.top();
    path.pop();
    connection = "--[" + movie + "#@" + year + "]-->(" + actor + ")";
    out << connection;
  }
}

/*
 * Function name: main
 * Description: This function process the arguments and call other function 
 *              to find the path
 */
int main (int argc, char * argv[]) {

  // check if there are correct argument passed in
  if (argc != 5) {
    cout << "Incorrect number of arguments." << endl;
    cout << "\t First argument: name of file containing the movie casts.\n";
    cout << "\t Second argument: u or w for unweighted/weighted edges\n";
    cout << "\t Third argument: name of file containing pairs of actors\n";
    cout << "\t Fourth argument: name of output file\n";
    cout << endl;
    exit(-1);
  }

  //process the second command line arg first
  bool weighted_edge = false;
  //if w, use weighted edge
  string weighted(argv[2]);
  if (weighted == "w") weighted_edge = true;
  
  //create the graph that stores the movies and casts
  ActorGraph graph;
  graph.build(argv[1], false);
  //create BFS for search path
  BFS bfs;
  bfs.connectGraph(weighted_edge, graph);


  //print the header to the out file
  ofstream out(argv[4]);
  out << "(actor)--[movie#@year]-->(actor)--...\n";

  //read the 3rd arg input file
  ifstream actorFile(argv[3]);
  bool have_header = false;
  while(actorFile) {
    // read a line and output a line each time
    string s;
    
    if (!getline( actorFile, s)) break;

    // check if it's the header line
    if (!have_header) {
      have_header = true;
      continue;
    }

    // get the two actor's name
    istringstream ss( s );
    vector<string> actor_pair;
    
    while(ss) {
      string next;
      if (!getline( ss, next, '\t' )) break;
      actor_pair.push_back( next );
    }
    
    if (actor_pair.size() != 2) continue;

    // check if these two actors are in the graph
    if (graph.all_actors.count(actor_pair[0]) == 0 || 
        graph.all_actors.count(actor_pair[1]) == 0) {
      // current pair does not exist, jump to the next pair
      cout << "actor is null" << endl;
      continue;
    }

    // get these two actors' vertices
    Vertex* actor1 = graph.all_actors[actor_pair[0]];
    Vertex* actor2 = graph.all_actors[actor_pair[1]];

    // a stack to store the shortest path
    stack<string> path;
    // a flag indicating this is used for pathfinder
    bool actor_connect = false;
    // finding the path and print it if it exists
    if (bfs.findpath(actor1, actor2, path, 2016, actor_connect)) {
      printpath(path, out);
    }

    out << "\n";
  }
  out.close();

  if (!actorFile.eof()) {
    cerr << "failed to read " << argv[3] << "!\n";
  }
  actorFile.close();

  return EXIT_SUCCESS;
}
