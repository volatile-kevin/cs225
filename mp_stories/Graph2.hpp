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

  bool found = false;

  std::queue<std::string> q;
  q.push(start);

  std::unordered_map<string, string> pred;
  pred.insert({start, start})
    while(!found){
      std::string current = q.front();
      q.pop();

      for(Edge & e : EList){
        if(e.dest().key() == end || e.source().key() == end){
          found = true;
        }
        if(parent.find(e.dest().key()) == parent.end()){
          q.push(e.dest().key());
          parent.insert({e.dest().key(), e.source().key()});
        }
        if(parent.find(e.source().key()) == parent.end()){
          q.push(e.source().key());
          parent.insert({e.source().key(), e.dest().key()});
        }
      }
    }

  return path;
}
