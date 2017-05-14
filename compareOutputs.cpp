
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char * argv[]) {
  
  vector<int> pathLengths1, pathLengths2;

  ifstream infile1(argv[1]);
  ifstream infile2(argv[2]);

  bool have_header = false;
  cout << "reading input file1...\n";
  while (infile1)
  {
    string s;
    if (!getline( infile1, s)) break;
    if (!have_header)
    {
      have_header = true;
      continue;
    }
    istringstream ss(s);
    int count = 0;
    while(ss)
    {
      string next;
      if(!getline( ss, next, '@' )) break;
      count++;
    }
    pathLengths1.push_back(count);
  }

  if (!infile1.eof())
  {
    cerr << "Failed to read " << argv[1] << "!\n";
    return false;
  }
  cout << "input file1 read.\n";


  have_header = false;
  cout << "reading input file2...\n";
  while (infile2)
  {
    string s2;
    if (!getline( infile2, s2)) break;
    if (!have_header)
    {
      have_header = true;
      continue;
    }
    istringstream ss2(s2);
    int count2 = 0;
    while(ss2)
    {
      string next2;
      if(!getline( ss2, next2, '@' )) break;
      count2++;
    }
    pathLengths2.push_back(count2);
    
    
  }

  if (!infile2.eof())
  {
    cerr << "Failed to read " << argv[2] << "!\n";
    return false;
  }
  cout << "input file2 read.\n";

  if (pathLengths1.size() != pathLengths2.size()) {
    cout << "Error: file: " << argv[1] << " has line #: " 
    << pathLengths1.size() << " while file: " << argv[2] << " has line #: "
    << pathLengths2.size() << endl;
    exit(-1);
  }
  bool noerror = true;
  cout << "number of paths: " << pathLengths1.size() << endl;
  for (unsigned int i = 0; i < pathLengths1.size(); i++) {
    if (pathLengths1[i] != pathLengths2[i]) {
      cout << "Path lengths differ at line number: " << i+2 << endl;
      noerror = false;
    }
  
  }
  if (noerror)
  cout << "\nCongrats! All paths are of same length! We good to go!\n";




}
