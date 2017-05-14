/*
 * File name: Edge.cpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#include "Edge.hpp"
using namespace std;

/*
 * Constructor that sets the edge's movie name and year, sets its weight, 1
 * as dump weighted for unweighted graph, (v, w) v for self and w for other
 */
Edge::Edge(string moviename, int year, bool weighted, Vertex* actor1, 
           Vertex* actor2) {
  this->moviename = moviename;
  this->year = year;
  if (weighted) weight = 1+(2015-year);
  else weight = 1;
  self = actor1;
  other = actor2;
}

