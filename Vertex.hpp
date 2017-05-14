/*
 * File name: Vertex.hpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <vector>
#include <climits>
#include <string>
#include "Edge.hpp"

class Edge;

/*
 * Description: This class is the vertex of the graph. Each actor is 
 *              represented by one vertex, inside the vertex there is an 
 *              adjacency list and 3 fields for the BST algorithm's marking
 */
class Vertex {
  friend bool comp();

  public:
    std::string name;   //name of the actor, later serves as the key to the unordered map
    std::vector<Edge> adj_list; //adjacency list
    unsigned int adjIndex;

    int dist;           //the distance from the starting vertex
    Edge* prev;         //the edge to the previous vertex
    Vertex* prevV;      //previous vertex, only used in UnionFind
    bool visited;       //flag to indicate if the vertex has been visited

    Vertex(std::string actor); //constructor
    ~Vertex();

    void reset();       //reset the vertex dist, prev, visited and preV
    void resetAdj();    //reset the vertex adj_list
};

#endif
