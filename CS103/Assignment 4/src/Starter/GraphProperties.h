/**
 * File: GraphProperties.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Code that uses the functions from GraphTheory.cpp to find the largest/smallest
 * independent sets, vertex covers, k-colorings, and cliques in a graph.
 */
#ifndef GraphProperties_Included
#define GraphProperties_Included

#include "GraphInternal.h"
#include <set>
#include <map>
#include <vector>
#include <functional>

/* Type: NodeSetPredicate
 *
 * Type reprsenting a predicate function that takes in a graph and a subset of its
 * nodes.
 */
using NodeSetPredicate = std::function<bool(Graph, std::set<Node>)>;

/* Type: ColorPredicate
 *
 * Type representing a predicate function that can check if a graph coloring is
 * correct.
 */
using ColorPredicate = std::function<bool(Graph, std::map<Node, Color>, size_t)>;



/* Given a graph, returns the largest independent set in that graph. */
std::set<Node> largestIndependentSetIn(const Graph& G, NodeSetPredicate isIS);

/* Given a graph, returns the smallest vertex cover in that graph. */
std::set<Node> minVertexCoverIn(const Graph& graph, NodeSetPredicate isVC);

/* Given a graph, returns the largest clique in that graph. */
std::set<Node> largestCliqueIn(const Graph& G, NodeSetPredicate isC);

/* Given a graph and a color palette, returns a minimum k-vertex coloring of that graph. */
std::map<Node, Color> kVertexColor(const Graph& graph, const std::vector<RealColor>& colors,
                                   ColorPredicate isColored);

#endif
