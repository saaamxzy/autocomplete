/*
 * File name: UnionFind.cpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#include "UnionFind.hpp"

using namespace std;

/*
 * Function name: reset
 * This function reset the sets
 */
void UnionFind::reset() {
  for(Vertex* v : resetList) {
    v->reset();
  }
}

/*
 * Function name: connectYear
 * This function creates edges for movies in a particular year in a graph
 * Returns true if edges are successfully inserted. False if that year does
 * not record any movie
 */
bool UnionFind::connectYear( int year, ActorGraph& graph ) {
  // return false if there is no movie at that year
  if ((graph.movies_by_year).count(year) == 0) return false;

  // to retrieve the list of movies in that year
  set<string> & movie_list = (graph.movies_by_year)[year];
  // go through all movies in that year
  for (auto it = movie_list.begin(); it != movie_list.end(); it++ ) {
    // get a movie
    Movie_cast* movie = graph.all_movies[*it];
    // pick the first actor Vertex in the movie cast as root
    Vertex* root = movie->cast.at(0);
    if (!root->visited) {
      // visit vertex if not visited
      root->visited = true;
      // The root of a set has a prevV that points to itself
      root->prevV = root;
      // add the root to the resetList
      resetList.push_back(root);
    } else {
      //find the root of this "root"
      while (root->prevV != root) {
        root = root->prevV;
      }
    }
    // this vertex pointer will store the very top root, if there is any
    Vertex* realRoot;
    for (unsigned int i = 1; i < movie->cast.size(); i++) {
      // go over the rest of the vertices and check
      Vertex* actor = movie->cast.at(i);
      if (!actor->visited) {
        // if not visited, then visit the root
        actor->prevV = root;
        actor->visited = true;
        // add it to the resetList
        resetList.push_back(actor);
      } else {
        // if the vertex is visited, the root of current set should be
        // changed
        realRoot = actor;
        while ( realRoot->prevV != realRoot ) {
          //loop all the way to the root
          realRoot = realRoot->prevV;
        }
        // make the current set's root pointing to the very top root
        root->prevV = realRoot;
        root = realRoot; 
      }
    }
  }
  return true;
}

/* Return the root of this vertex */
Vertex* UnionFind::find( Vertex* actor ) {
  Vertex* result;
  // not in a set, return null
  if (!actor->prevV) return 0;
  result = actor;
  while (result->prevV != result) {
    // go to the very top parent root
    result = result->prevV; 
  }
  return result;
} 

