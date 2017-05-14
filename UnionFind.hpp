/*
 * File name: UnionFind.hpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include "Vertex.hpp"
#include "ActorGraph.hpp"
#include <iostream>
#include <string>
#include <vector>

/* Class that performs the Union find algorithm for 
 * actorconnections
 */
class UnionFind {
  
  public:
    // This method add edges to graph using movies in a particular year
    bool connectYear( int year, ActorGraph& graph);
    // Returns the root of actor
    Vertex* find( Vertex* actor );
    // Reset all prevV pointers in a graph
    void reset();

  private:
    // to store all prevV pointers needed to be reset
    std::vector<Vertex*> resetList;

};

#endif
