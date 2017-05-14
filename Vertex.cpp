/*
 * File name: Vertex.cpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#include "Vertex.hpp"

using namespace std;

/*
 * Constructor which set the vertex actor name. dist to infinity, prev and
 * prevV to 0, and unvisited
 */
Vertex::Vertex(string actor) {
  name = actor;
  dist = INT_MAX;
  adjIndex = 0;
  prev = 0;
  prevV = 0;
  visited = false;  
}
Vertex::~Vertex() {
  delete prev;
  delete prevV;
  adj_list.clear();
}
/*
 * Reset the dist, prev, prevV, and visited to initial value
 */
void Vertex::reset() {
  dist = INT_MAX;
  prev = 0;
  prevV = 0;
  visited = false;
  adjIndex = 0;
}

/*
 * Reset the adj_list
 */
void Vertex::resetAdj() {
}
