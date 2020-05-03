#include "GraphProperties.h"
#include "Utilities.h"
#include <vector>
using namespace std;

/* Private helper functions. */
namespace {
    bool recHasIndependentSet(const Graph& graph, size_t k,
                              const vector<Node>& allNodes, size_t index,
                              set<Node>& result,
                              NodeSetPredicate isIS) {
        /* Base case: If the graph is too small, abort. */
        if ((graph.size() - index) + result.size() < k) return false;

        /* Base case: If we have a set of size k, confirm that it's legit (it should be,
         * but the student code may be incorrect) and take things from there.
         */
        if (result.size() == k) {
            return isIS(graph, result);
        }

        /* Recursive case: Look at this node. We either include it or exclude it. */
        if (recHasIndependentSet(graph, k, allNodes, index + 1, result, isIS)) {
            return true;
        }

        /* See if we can include it. */
        result.insert(allNodes[index]);
        if (isIS(graph, result) &&
            recHasIndependentSet(graph, k, allNodes, index + 1, result, isIS)) {
            return true;
        }

        /* Oops, not possible. */
        result.erase(allNodes[index]);
        return false;
    }

    /* Uses the provided oracle to find the largest possible independent set in G.
     * This works by incrementally choosing whether to include or exclude nodes
     * and using the oracle on the sets we propose to see what works best.
     */
    bool hasIndependentSet(const Graph& graph, size_t k, set<Node>& output,
                           NodeSetPredicate pred) {
        /* For simplicity, begin by getting a list of all the nodes in the graph. */
        vector<Node> allNodes;
        for (const auto& entry: graph) {
            allNodes.push_back(entry.first);
        }

        return recHasIndependentSet(graph, k, allNodes, 0, output, pred);
    }

    bool recHasVertexCoverOfSize(const Graph& master, size_t k,
                                 const vector<Node>& nodes, size_t index,
                                 Graph soFar, set<Node>& result,
                                 NodeSetPredicate isVC) {
        /* Base case: If we have too many nodes, we're done. */
        if (result.size() > k) return false;

        /* Base case: If we've processed everything, we should have a vertex cover
         * of the right size. However, we need to validate that the student code
         * works properly on this case.
         */
        if (index == nodes.size()) {
            return isVC(master, result);
        }

        /* Incorporate the next node into the graph. */
        soFar[nodes[index]] = {}; // Initially, no outgoing links.

        for (Node dest: master.at(nodes[index])) {
            /* If this node is already in our graph fragment, add this edge into the
             * graph fragment.
             *
             * Fun fact: the proper term for this type of graph is an "induced subgraph,"
             * since it consists of a bunch of nodes from the original graph and all the
             * original edges between them.
             */
            if (soFar.count(dest)) {
                soFar[dest].insert(nodes[index]);
                soFar[nodes[index]].insert(dest);
            }
        }

        /* We now have two options:
         *
         * 1. Skip this node, if the induced subgraph is currently all set. If the current
         *    induced subgraph isn't covered by what we have, it means that there is some
         *    edge where we've already decided not to include an old endpoint, and by excluding
         *    the current node we have an edge that can never be covered by other nodes.
         * 2. Include this node.
         */

        if (isVC(soFar, result) &&
            recHasVertexCoverOfSize(master, k, nodes, index + 1, soFar, result, isVC)) {
            return true;
        }

        /* That didn't work. We have to add this node. */
        result.insert(nodes[index]);
        if (recHasVertexCoverOfSize(master, k, nodes, index + 1, soFar, result, isVC)) {
            return true;
        }

        /* Oops, that didn't work. */
        result.erase(nodes[index]);
        return false;
    }

    /* Uses the provided oracle to determine whether the graph has a small
     * vertex cover. This works by incremenetally selecting an unchosen node,
     * adding it into a larger induced subgraph, and then seeing what happens when we
     * do and do not include it.
     */
    bool hasVertexCoverOfSize(const Graph& graph, size_t k, set<Node>& output,
                              NodeSetPredicate isVC) {
        /* For simplicity, begin by getting a list of all the nodes in the graph. */
        vector<Node> allNodes;
        for (const auto& entry: graph) {
            allNodes.push_back(entry.first);
        }

        return recHasVertexCoverOfSize(graph, k, allNodes, 0, {}, output, isVC);
    }

    bool recHasClique(const Graph& graph, size_t k,
                      const vector<Node>& allNodes, size_t index,
                      set<Node>& result, NodeSetPredicate isC) {
        /* Base case: If the graph is too small, abort. */
        if ((graph.size() - index) + result.size() < k) return false;

        /* Base case: If we have a set of size k, confirm that it's legit (it should be,
         * but the student code may be incorrect) and take things from there.
         */
        if (result.size() == k) {
            return isC(graph, result);
        }

        /* Recursive case: Look at this node. We either include it or exclude it. */
        if (recHasClique(graph, k, allNodes, index + 1, result, isC)) {
            return true;
        }

        /* See if we can include it. */
        result.insert(allNodes[index]);
        if (isC(graph, result) &&
            recHasClique(graph, k, allNodes, index + 1, result, isC)) {
            return true;
        }

        /* Oops, not possible. */
        result.erase(allNodes[index]);
        return false;
    }

    /* Uses the provided oracle to find the largest possible clique in graph G.
     * This works by incrementally choosing whether to include or exclude nodes
     * and using the oracle on the sets we propose to see what works best.
     */
    bool hasClique(const Graph& graph, size_t k, set<Node>& output, NodeSetPredicate isC) {
        /* For simplicity, begin by getting a list of all the nodes in the graph. */
        vector<Node> allNodes;
        for (const auto& entry: graph) {
            allNodes.push_back(entry.first);
        }

        return recHasClique(graph, k, allNodes, 0, output, isC);
    }

    bool recHasKColoring(const Graph& master, size_t k,
                         const vector<Node>& nodes, size_t index,
                         size_t maxColorUsed,
                         Graph soFar, map<Node, Color>& result,
                         const vector<RealColor>& colors,
                         ColorPredicate isColored) {
        /* Base case: If all nodes are assigned colors, the graph should be colored.
         * However, we have to ask the oracle this, since the oracle might be (eh hem)
         * incorrect.
         */
        if (index == nodes.size()) {
            return isColored(master, result, k);
        }

        /* Otherwise, incorporate the new node into the graph. */
        soFar[nodes[index]] = {}; // Initially, no outgoing links.

        for (Node dest: master.at(nodes[index])) {
            /* If this node is already in our graph fragment, add this edge into the
             * graph fragment.
             *
             * Fun fact: the proper term for this type of graph is an "induced subgraph,"
             * since it consists of a bunch of nodes from the original graph and all the
             * original edges between them.
             */
            if (soFar.count(dest)) {
                soFar[dest].insert(nodes[index]);
                soFar[nodes[index]].insert(dest);
            }
        }

        /* Now, see what colors we can use here.
         *
         * There are a couple of guiding principles:
         *
         *   1. We can never use more than k colors.
         *   2. There is never a reason to use more than n colors, where
         *      n is the total number of nodes.
         *   3. If we've only used z total colors so far, we should never
         *      consider more than z+1 of them.
         *
         * All of these are rolled into this loop condition.
         */
        for (size_t i = 0; i < k && i <= index && i <= maxColorUsed; i++) {
            if (i >= colors.size()) {
                Utilities::error("Oops - we asked for more colors than our driver code has available!");
            }

            /* Try coloring the node. */
            result[nodes[index]] = &colors[i];

            /* If this is a legal coloring and can be extended further, great!
             * We're done.
             */
            if (isColored(soFar, result, k) &&
                recHasKColoring(master, k, nodes, index + 1,
                                maxColorUsed + !!(i == maxColorUsed), soFar, result, colors, isColored)) {
                return true;
            }

            /* Oops, try the next color. */
        }

        /* Remove this color assignment and signal failure. */
        result.erase(nodes[index]);
        return false;
    }

    /* Uses the provided oracle oracle to determine whether the graph has a
     * k-coloring. This works by incremenetally selecting an uncolored node,
     * then iterating over all possible colors for which the oracle reports
     * that the graph fragment is k-colored.
     */
    bool hasKColoring(const Graph& graph, size_t numColors, map<Node, Color>& output,
                      const vector<RealColor>& colors,
                      ColorPredicate isColored) {
        /* For simplicity, begin by getting a list of all the nodes in the graph. */
        vector<Node> allNodes;
        for (const auto& entry: graph) {
            allNodes.push_back(entry.first);
        }

        return recHasKColoring(graph, numColors, allNodes, 0, 0, {}, output, colors, isColored);
    }
}

set<Node> largestIndependentSetIn(const Graph& G, NodeSetPredicate isIS) {
    /* Binary search to find the largest size. */
    size_t low  = 1;            // Exclusive; we know anything lower than this works.
    size_t high = G.size() + 1; // Inclusive; we know that this and anything higher doesn't work.

    /* We have to be able to work on something of size zero. */
    set<Node> result;
    if (!isIS(G, result)) {
        Utilities::error("Your code fails on an important edge case.");
    }

    while (low != high) {
        size_t size = low + (high - low) / 2;

        set<Node> indSet;
        if (hasIndependentSet(G, size, indSet, isIS)) {
            result = indSet;
            low = size + 1;
        } else {
            high = size;
        }
    }

    return result;
}

set<Node> largestCliqueIn(const Graph& G, NodeSetPredicate pred) {
    /* Binary search to find the largest size. */
    size_t low  = 1;            // Exclusive; we know anything lower than this works.
    size_t high = G.size() + 1; // Inclusive; we know that this and anything higher doesn't work.

    /* We have to be able to work on something of size zero. */
    set<Node> result;
    if (!pred(G, result)) {
        Utilities::error("Your code fails on an important edge case.");
    }

    while (low != high) {
        size_t size = low + (high - low) / 2;

        set<Node> indSet;
        if (hasClique(G, size, indSet, pred)) {
            result = indSet;
            low = size + 1;
        } else {
            high = size;
        }
    }

    return result;
}

/* Computes a minimum vertex cover using the provided student code. */
set<Node> minVertexCoverIn(const Graph& graph, NodeSetPredicate pred) {
    /* Pessimistically assume we need all nodes. */
    set<Node> result;
    for (const auto& entry: graph) {
        result.insert(entry.first);
    }

    /* We should be able to color the graph with one color per node. Make sure
     * that the student solution allows for this.
     */
    if (!pred(graph, result)) {
        Utilities::error("Your code failed an important edge case test.");
    }

    /* Use binary search over the possible number of colors needed. */
    size_t low  = 0;            // Exclusive; we know anything lower is wrong.
    size_t high = graph.size(); // Inclusive; we know this one works

    while (low != high) {
        size_t mid = low + (high - low) / 2;

        set<Node> thisCover;
        if (hasVertexCoverOfSize(graph, mid, thisCover, pred)) {
            result = thisCover;
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return result;
}

/* Computes a minimum k-coloring and colors all nodes appropriately. */
map<Node, Color> kVertexColor(const Graph& graph, const vector<RealColor>& colors,
                              ColorPredicate pred) {
    map<Node, Color> result;

    /* We should be able to color the graph with one color per node. Make sure
     * that the student solution allows for this.
     */
    if (!hasKColoring(graph, graph.size(), result, colors, pred)) {
        Utilities::error("Unable to color an n-node graph with n colors?");
    }

    /* Use binary search over the possible number of colors needed. */
    size_t low  = 0;            // Exclusive; we know anything lower is wrong.
    size_t high = graph.size(); // Inclusive; we know this one works

    while (low != high) {
        size_t mid = low + (high - low) / 2;

        map<Node, Color> thisColoring;
        if (hasKColoring(graph, mid, thisColoring, colors, pred)) {
            result = thisColoring;
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return result;
}
