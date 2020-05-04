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
    //保证子集的关系
    for(auto node:C)
        if(!G.count(node))
            return false;


    for(auto temp:G)
    {
        auto node1=temp.first;
        if(C.count(node1))
            continue;
        for(auto node2:temp.second)
            if(!C.count(node2))
                return false;
    }
    return true;
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
    for(auto g:G)
    {
        auto node1=g.first;
        auto color1=colors[node1];
        for(auto node2:g.second)
        {
            auto color2=colors[node2];
            if(color1==color2)
                return false;
        }
    }
    return true;
}

/* Given a graph G = (V, E) and a set K subset V, returns whether
 * K is a clique in G.
 */
bool isClique(Graph G, std::set<Node> K) {
    for(auto node1:K)
    {
        for(auto node2:K)
        {
            if(node1==node2)
                continue;
            if(!G[node1].count(node2)&&!G[node2].count(node1))
                return false;
        }
    }
    return true;
}
