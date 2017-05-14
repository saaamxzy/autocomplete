/*
 * File name: Edge.hpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#ifndef EDGE_HPP
#define EDGE_HPP
#include <string>
#include "Vertex.hpp"

class Vertex;

/*
 * This class is the directed edge of the graph. It represents an edge from 
 * actor1 to actor2. It contains a name of the movie, both actors, the year of 
 * the movie, and the weight of the edge. 
 * It has 2 ptrs points to the first actor and the second one
 */
class Edge {

  public:
    std::string moviename;    
    int year;
    int weight;
    Vertex* self;
    Vertex* other;

    Edge(std::string moviename, int year, bool weighted, 
         Vertex* actor1, Vertex* actor2);  //constructor
};

#endif
