/* Program to generate pairs of actors from a movie cast file. */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

void toVec(unordered_set<string> actors, vector<string> & actorsVec, int num) {
  cout << "converting to shuffled vector...\n";
  int count = 0;
  auto actor = actors.begin();
  
  while (actor != actors.end() && count < num) {
    actorsVec.push_back(*actor);  
    actor++;
    count++;
  }
  random_shuffle(actorsVec.begin(), actorsVec.end());

}

void writePairs( ofstream & out, vector<string> & actorVec ){
  out << "Actor1  Actor2\n";
  while( !actorVec.empty() ) {
    out << actorVec.back() << "\t";
    actorVec.pop_back();
    if (actorVec.empty()) return;
    out << actorVec.back() << "\n";
    actorVec.pop_back();
  }
}


int main(int argc, char * argv[]) {

  if (argc != 4) {
    cout << "Incorrect number of arguments." << endl;
    cout << "\t First argument: name of file containing the movie casts.\n";
    cout << "\t Second argument: name of output file\n";
    cout << "\t Third argument: number of actors want to generate\n"; 
    cout << endl;
    exit(-1);
  }

  unordered_set<string> actorNames;
  ifstream infile(argv[1]);

  bool have_header = false;
  cout << "reading input file...\n";
  while (infile)
  {
    string s;
    if (!getline( infile, s)) break;
    if (!have_header)
    {
      have_header = true;
      continue;
    }
    istringstream ss(s);
    vector<string> record;
    while(ss)
    {
      string next;
      if(!getline( ss, next, '\t' )) break;
      record.push_back( next );
    }
    if (record.size() != 3) continue;
    actorNames.insert(record[0]);
  }

  if (!infile.eof())
  {
    cerr << "Failed to read " << argv[1] << "!\n";
    return false;
  }
  cout << "input file read.\n";

  infile.close();
  vector<string> actorVec;
  int numActors = stoi(argv[3]);
  cout << "\n converting to a shuffled vector... \n";
  toVec(actorNames, actorVec, numActors);
  ofstream out(argv[2]);
  cout << "\n writing to output file... \n";
  writePairs( out, actorVec);
  out.close();
  cout << "\n done. \n";
}

