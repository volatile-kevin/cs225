#include "Graph.h"
#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;

  std::queue<std::string> q;
  q.push(start);

  std::unordered_map<std::string, std::string> theRents;
  theRents.insert({start, start});

  int visited = 0;
  int poopscoophoopitydoop = 0;
  while(visited == 0){
    std::string curr = q.front();
    q.pop();

    std::list<std::reference_wrapper<E>> edges = incidentEdges(curr);
    for(Edge & e : edges){
      if(theRents.find(e.source().key()) == theRents.end()){
        q.push(e.source().key());
        theRents.insert({e.source().key(), e.dest().key()});
      }
      if(theRents.find(e.dest().key()) == theRents.end()){
        q.push(e.dest().key());
        theRents.insert({e.dest().key(), e.source().key()});
      }
      if(e.source().key() == end || e.dest().key() == end){
        visited = 1;
      }
    }
  }

  std::string tempPoo = end;
  while(!poopscoophoopitydoop){
    if(tempPoo == start){
      poopscoophoopitydoop = 1;
    }
    path.push_front(tempPoo);
    tempPoo = theRents.at(tempPoo);
  }
  return path;
}
