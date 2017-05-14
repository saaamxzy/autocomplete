/*
 * File name: actorconnections.cpp
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#include <queue>
#include <fstream>
#include <string>
#include "Vertex.hpp"
#include "ActorGraph.hpp"
#include "Edge.hpp"
#include "BFS.hpp"
#include "UnionFind.hpp"



using namespace std;

/*
 * Function name: printResult
 * This method prints out the result of finding path
 */
void printResult (Vertex* actor1, Vertex* actor2, int year, ofstream & out ) {
  out << actor1->name + "\t" + actor2->name + "\t" + to_string(year) + "\n";
}


void printResult (string actor1, string actor2, int year, ofstream & out ) {
  out << actor1 + "\t" + actor2 + "\t" + to_string(year) + "\n";
}


int main(int argc, char * argv[]) {
  if (argc != 4 && argc != 5) {
    cout << "Incorrect number of arguments." << endl;
    cout << "\t First argument: name of file containing the movie casts.\n";
    cout << "\t Second argument: name of file containing pairs of actors\n";
    cout << "\t Third argument: name of output file\n";
    cout << "\t Fourth argument (optional): bfs or ufind for algorithm\n"; 
    cout << endl;
    exit(-1);
  }

  // set the default algorithm to ufind
  bool use_bfs = false;

  // check the algorithm flag
  if (argc == 5) {
    string s(argv[4]);
    if (s == "bfs") use_bfs = true;
  }

  //build the graph with vertices not connected by any edge yet
  bool actor_connect = true;
  ActorGraph graph;
  graph.build(argv[1], actor_connect);

  // connect vertices if using bfs
  if (use_bfs) {
    BFS bfs;
    bfs.connectGraph(false, graph);
  }

  // writing the header
  ofstream out(argv[3]);
  out << "Actor1\tActor2\tYear\n";

  ifstream actorFile(argv[2]);
  bool have_header = false;
  
  while(actorFile) {
    string s;
    
    if (!getline( actorFile, s)) break;

    if (!have_header) {
      have_header = true;
      continue;
    }

    // get the two actors vertices that we wanna find connection
    istringstream ss( s );
    vector<string> actor_pair;
    
    while(ss) {
      string next;
      if (!getline( ss, next, '\t' )) break;
      actor_pair.push_back( next );
    }
    
    if (actor_pair.size() != 2) continue;

    if (graph.all_actors.count(actor_pair[0]) == 0 || 
        graph.all_actors.count(actor_pair[1]) == 0) {
      // current pair does not exist, jump to the next pair
      printResult(actor_pair[0], actor_pair[1], 9999, out);
      continue;
    }
    Vertex* actor1 = graph.all_actors[actor_pair[0]];
    Vertex* actor2 = graph.all_actors[actor_pair[1]];

    // add each year's movie and connect the graph correspondingly
    // keeps checking if this two actors are connected, if so, output
    // the result
    bool found = false;
    UnionFind uf;
    if (use_bfs) {
      // bfs algorithm
      // add movies year by year, and check if two actors are connected
      // after adding certain year's movies to the graph
      BFS bfs;
      for (auto it = (graph.movies_by_year).begin(); 
           it != (graph.movies_by_year).end(); it++) {
        int year = it->first;
        // add edges of that year
        // stack to hold the path
        stack<string> path_dontcare;
        // flag indicating findpath is used for actorconnections
        bool actor_connect = true;
        // if a path is found, break out of the loop
        if (bfs.findpath(actor1, actor2, path_dontcare, year, actor_connect)) {
          found = true;
          printResult(actor1, actor2, year, out);
          break;
        }
      }
    } else {
      // union actors year by year
      for (auto it = (graph.movies_by_year).begin(); 
           it != (graph.movies_by_year).end(); it++) {
        int year = it->first;
        if(!uf.connectYear(year, graph)) continue;
        Vertex* result1 = uf.find(actor1);
        Vertex* result2 = uf.find(actor2);
        // check if two actors are unioned
        if (result1 == result2
            && result1 != 0 && result2 != 0) {
          found = true;
          // if so, print out the result
          printResult(actor1, actor2, year, out);
          uf.reset();
          break;
        }
      }
    }
    // if not found, print 9999
    if (!found) {
      int notFound = 9999;
      printResult(actor1, actor2, notFound, out);
    }
  
  }
  out.close();

  if (!actorFile.eof()) {
    cerr << "failed to read " << argv[3] << "!\n";

  }
  actorFile.close();
}
