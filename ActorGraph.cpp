/*
 * File name: ActorGraph.cpp 
 * Name: Yunlu Huang
 * Student ID: A91008991 
 * Partner Name: Zhengyuan Xu
 * Partner ID: A99076427
 * Date: Aug 30, 2016
 */
#include "ActorGraph.hpp"

using namespace std;


/*
 * Function name: loadFromFile()
 * Parameters: const char* in_filename
 *             bool actor_connect
 * Description: This function loads the movie and actor informations from the
 *              file, and build the graph from those information. It takes
 *              a actor_connect flag, so when actorconnection calls this
 *              function. It builds an extra map with lists of same year
 *              movies.
 */
bool ActorGraph::build(const char* in_filename, bool actor_connect)
{
 // Initialize the file stream
  ifstream infile(in_filename);
  bool have_header = false;
  // keep reading lines until the end of file is reached
  while (infile)
  {
    string s;
    // get the next line
    if (!getline( infile, s )) break;
    if (!have_header)
    {
      // skip the header
      have_header = true;
      continue;
    }
    istringstream ss( s );
    vector <string> record;
    while (ss)
    {
      string next;
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;
      record.push_back( next );
    }
    if (record.size() != 3)
    {
      // we should have exactly 3 columns
      continue;
    }

    //build the graph for pathfinder or actorconnection
    buildMap(record, actor_connect);
  }
  
  if (!infile.eof())
  {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();
 
  return true;
	
}

/*
 * Function name: buildMap
 * Description: This function build 2 maps, one contains all actor vertexes.
 *              the other one conatins all movies; if the actor_connect flag
 *              is set, a third map is built to contain lists of movies in
 *              the same year 
 */
bool ActorGraph::buildMap (vector<string> &record, bool actor_connect) {

  if (record.size() != 3) return false;

  string actor = record[0];
  string movie = record[1];
  int year = stoi(record[2], nullptr, 10);
  string movieKey = movie + "\t" + record[2];

  //insert the actor Vertex to the unordered_map
  pair<string, Vertex*> actorV(actor, new Vertex(actor));
  all_actors.insert(actorV);
  toDelete.push_back(actorV.second);
  


  //insert the movie vector to the unordered_map all_movies
  if (all_movies.count(movieKey) == 0) {
    all_movies[movieKey] = new Movie_cast(movie, year);
    moviesToDelete.push_back(all_movies[movieKey]);
  }
  //add the actor vertex ptr to that movie's actors list
  (all_movies[movieKey]->cast).push_back( all_actors[actor] );

  //build the extra map by year if it's used for actorconnection
  if (actor_connect) {
    //add each movie's movieKey to the corresponding year
    movies_by_year[year].insert(movieKey);
  }

  return true;
}

ActorGraph::~ActorGraph() {
  
  for (unsigned int i = 0; i < toDelete.size(); ++i) {
    delete toDelete[i];
  }

  for (unsigned int i = 0; i < moviesToDelete.size(); ++i) {
    delete moviesToDelete[i];
  }
  
  all_actors.clear();
  all_movies.clear();
}
