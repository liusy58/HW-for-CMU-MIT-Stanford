/**
 * File: GraphVisualizer.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Functionality to display a graph, along with a specific set of highlighted
 * nodes.
 */

#ifndef LogicVisualizer_Included
#define LogicVisualizer_Included

#include "GraphTheory.h"
#include <string>

/* Displays a graph, with each node given a different color. */
void visualizeGraph(const Graph& g, const std::string& title,
                    const std::string& errorMessage, const std::map<Node, Color>& colors);

#endif
