/*
 * File name: BFS.hpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#ifndef BFS_HPP
#define BFS_HPP

#include "Vertex.hpp"
#include "ActorGraph.hpp"
#include <iostream>
#include <stack>
#include <string>
#include <queue>

class Vertex;

/*
 * Overloading comparison method for priority queue
 */
class VertexCmp {
public:
  bool operator()(Vertex*& lhs, Vertex*& rhs) const {
    return lhs->dist > rhs->dist;
  } 
};

/*
 * This class performs the bfs algorithm for both pathfinder and 
 * actorconnections
 */
class BFS {

  public:
    // This method add all edges to the graph
    void connectGraph (bool weighted, ActorGraph& graph); 
    // This method finds if two actors are connected, and record the shortest
    // path in a stack; it takes a flag indicating if this is used for
    // actor connect or not
    bool findpath (Vertex* start, Vertex* end, std::stack<std::string>& path, int year, bool actor_connect);
};

#endif
