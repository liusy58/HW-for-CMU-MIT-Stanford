#ifndef GraphTheory_Included
#define GraphTheory_Included

#include <map>
#include <set>
#include <cstddef>

/* Type: Node
 *
 * A type representing a node in a graph.
 */
using Node = struct RealNode*;

/* Type: Color
 *
 * A type representing a color.
 */
using Color = const struct RealColor*;

/* Type: Graph
 *
 * A type representing a graph. For the purposes of this assignment, the nodes
 * in each graph will be integers.
 *
 * Unlike in class, where we represent graphs as an ordered pair (V, E), for
 * this assignment we'll be representing graphs using a data structure called
 * an adjacency list. In this representing, the graph is represented by a map
 * whose keys are the nodes and where each value is the list of nodes the key
 * is adjacent to. For example, consider this graph:
 *
 *         A --- B     F
 *         | \   |
 *         |  \  |
 *         |   \ |
 *         D --- C --- E
 *
 * This graph would be represented as an adjacency list as follows:
 *
 *       key | value
 *      -----+------------
 *        A  | B, C, D
 *        B  | A, C
 *        C  | A, B, D, E
 *        D  | A, C
 *        E  | C
 *        F  |
 *
 * This representation is commonly used in practice, and if you take CS161 you'll
 * learn about some of the reasons why that is. Notice, importantly, that every
 * edge { u, v } is represented twice, once when u is the key and once when v
 * is the key.
 *
 * This version of the map is the one from the C++ standard library. For the
 * purposes of this assignment, you'll probably want to know the following
 * operations:
 *
 * Iterate over nodes in the graph:
 *
 *    for (auto entry: myMap) {
 *        Node u = entry.first;
 *        // ... do something with u ... //
 *    }
 *
 * Iterate over the edges leaving a given node u in a graph:
 *
 *    for (Node v: myMap[u]) {
 *         // { u, v } is an edge in G
 *    }
 *
 * Look up all edges leaving a given node in the graph:
 *
 *     std::set<Node> linked = myMap[node];
 *
 * Here's quick refresher on how to use a std::set.
 *
 * Insert an element into a set:
 *
 *     std::set<T> mySet;
 *     mySet.insert(value);
 *
 * Remove an element from a set:
 *
 *     std::set<T> mySet;
 *     mySet.erase(value);
 *
 * As a reminder, you can iterate over the contents of a std::set by writing
 *
 *     for (T elem: mySet) {
 *        ...
 *     }
 *
 * You can check whether an element is present in a std::set by writing
 *
 *     if (mySet.count(x)) {
 *         ...
 *     }
 *
 * You can insert into a std::set by writing
 *
 *     mySet.insert(x);
 *
 * and you can get the cardinality of a set by writing
 *
 *     mySet.size();
 */
using Graph = std::map<Node, std::set<Node>>;

/* Your task is to implement these predicate functions. */
bool isIndependentSet(Graph G, std::set<Node> I);
bool isVertexCover(Graph G, std::set<Node> C);
bool isKVertexColoring(Graph G, std::map<Node, Color> colors, std::size_t k);
bool isClique(Graph G, std::set<Node> K);

#endif
