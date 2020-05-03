#include "GraphTheory.h"
#include <stdexcept>

/* Given a graph G = (V, E) and a set I subset V, returns whether
 * I is an independent set in G.
 */
bool isIndependentSet(Graph G, std::set<Node> I) {
    for(auto node:I)
    {
        if(!G.count(node))
            continue;
        auto node_set=G[node];
        for(auto node2:node_set)
            if(I.count(node2))
                return false;
    }
    return true;
}

/* Given a graph G = (V, E) and a set C subset V, returns whether
 * C is a vertex cover of G.
 */
bool isVertexCover(Graph G, std::set<Node> C) {
    /* TODO: Delete this line, the next three lines, and implement this function. */
    (void) G; // Silence compiler warnings about unused parameters
    (void) C;
    throw std::runtime_error("Not implemented!");
}

/* Given a graph G, a map assigning colors to all the nodes in G, and a number k,
 * returns whether the specified set of colors is a k-vertex-coloring of G.
 *
 * Every node in the graph is guaranteed to be a key in the map, and the map will
 * have no other keys.
 *
 * There may be more than k colors assigned to nodes by the colors map. You will need
 * to confirm that the number of colors used is AT MOST k. It's possible that fewer
 * than k colors will be used, and that's okay; a k-vertex-coloring doesn't necessarily
 * need to use all k colors.
 */
bool isKVertexColoring(Graph G, std::map<Node, Color> colors, std::size_t k) {
    /* TODO: Delete this line, the next four lines, and implement this function. */
    (void) G; // Silence compiler warnings about unused parameters
    (void) colors;
    (void) k;
    throw std::runtime_error("Not implemented!");
}

/* Given a graph G = (V, E) and a set K subset V, returns whether
 * K is a clique in G.
 */
bool isClique(Graph G, std::set<Node> K) {
    /* TODO: Delete this line, the next three lines, and implement this function. */
    (void) G; // Silence compiler warnings about unused parameters
    (void) K;
    throw std::runtime_error("Not implemented!");
}
