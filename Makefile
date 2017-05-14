CC=g++
CXXFLAGS= -std=c++11 -g -Wall -gdwarf-2
LDFLAGS= -g

all: pathfinder actorconnections
pathfinder: Vertex.o Edge.o ActorGraph.o BFS.o
actorconnections: Vertex.o Edge.o ActorGraph.o BFS.o UnionFind.o
Vertex.o: Vertex.hpp 
Edge.o: Edge.hpp 
ActorGraph.o: ActorGraph.hpp
BFS.o: BFS.hpp
UnionFind.o: UnionFind.hpp

clean:
	rm -f pathfinder actorconnections *.o core*
