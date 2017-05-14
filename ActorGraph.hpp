/*
 * File name: ActorGraph.hpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>
#include "Vertex.hpp"


class Vertex;

/*
 * A small class which stores the name and cast of one movie
 */
class Movie_cast {
  public:
    std::string moviename;
    int year;
    std::vector<Vertex*> cast;
    Movie_cast(std::string moviename, int year) {
      this->moviename = moviename;
      this->year = year;
    }
};

/*
 * This class stores all vertices info and movie's info.
 */
class ActorGraph {
     
  public:
    std::unordered_map<std::string, Vertex*> all_actors;
    std::unordered_map<std::string, Movie_cast*> all_movies;
    // this map contains lists of movies' names in the same year, the lists' 
    // keys are the year
    std::map<int, std::set<std::string>> movies_by_year;

    // desctructor
    ~ActorGraph();

   /**
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as
     * 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool build(const char* in_filename, bool actor_connect);

  private:
    std::vector<Vertex*> toDelete;
    std::vector<Movie_cast*> moviesToDelete;
    // helper method the build each vertex
    bool buildMap(std::vector<std::string> & record, bool actor_connect);
};


#endif // ACTORGRAPH_HPP
