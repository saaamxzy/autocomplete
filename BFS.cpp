/*
 * File name: BFS.cpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#include "BFS.hpp"

using namespace std;


/*
 * Function name: connectGraph()
 * Parameters: bool weighted
 * Description: This function connects all edges at once, it takes a weighted
 *              flag to treat the edges as weighted or not.
 */
void BFS::connectGraph (bool weighted, ActorGraph& graph) {
  //loop through each movie's list in all_movies map to connect actors by edge
  for (auto it = graph.all_movies.begin(); it != graph.all_movies.end(); it++) {
    Movie_cast* movie = it->second;
    //loop through the list to fill each actor's adj_list
    for (Vertex* actor: movie->cast ) {
      Vertex* self = actor;
        //loop through the list to add all other actors to current actors adj_list
      for (Vertex* other: movie->cast) {
        if (self == other) continue;
        //construct a new edge
        string moviename = movie->moviename;
        int year = movie->year;
        //add the edge to current actor's adj_list
        self->adj_list.push_back(Edge(moviename, year, weighted, self, other));
      }
    }
  }
}



/* 
 * Function name: findpath
 * This method finds if two actors are connected, and record the shortest
 * path in a stack; it takes a flag indicating if this is used for
 * actor connect or not
 */
bool BFS::findpath (Vertex* start, Vertex* end, stack<string>& path, 
                    int year, bool actor_connect) {

  // priority queue to add the adj vertices
  priority_queue<Vertex*, vector<Vertex*>, VertexCmp> q;
  // stack to record which vertex needs to be reset after searching
  stack<Vertex*> resetList;

  // set the starting actor as the beginning
  start->dist = 0;
  resetList.push(start);
  q.push(start);

  // a traversal pointer
  Vertex* cur; 
  // keeps looking while there's vertices in the queue
  while(!q.empty()) {
    // get the front of the queue
    cur = q.top();
    q.pop();
    // if the actor has not been visited, visit it and adds its neighbor
    if (!cur->visited) {
      cur->visited = true;
      // checking its neighbor
      for (Edge &outE: cur->adj_list) {
        if (outE.year <= year ) {
          Vertex* neighbor = outE.other;
          // calculate the new distance
          int newDist = cur->dist + outE.weight;
          // if the new distance is less than the neighbor's old dist, update it
          if (newDist < neighbor->dist) {
            neighbor->prev = &outE;
            neighbor->dist = newDist;
            // add the neighbor to the queue
            q.push(neighbor);
            resetList.push(neighbor);
          } 
        }
      }
    }
    if (cur == end) break;
  } 

  //if no path is found, return false 
  if (end->prev == 0) {
    //reset the vertices
    while (!resetList.empty()) {
      resetList.top()->reset();
      resetList.pop();
    }
    return false;
  }

  // for pathfinder only: traverse back from the ending actor to build the
  // shortest path
  if (!actor_connect) {
    //rebuild the path
    while (cur->prev) {
      string actorname = cur->name;
      string moviename = cur->prev->moviename;
      string yearString = to_string(cur->prev->year);
      path.push(actorname);
      path.push(moviename);
      path.push(yearString);
      cur = cur->prev->self; 
    }
    path.push(cur->name);
  }

  //reset the vertices info 
  while (!resetList.empty()) {
    resetList.top()->reset();
    resetList.pop();
  }

  // return true if successfully find the path
  return true;
}
