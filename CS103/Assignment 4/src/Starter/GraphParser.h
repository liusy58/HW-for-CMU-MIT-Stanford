/**
 * File: GraphParser.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Exports functions needed to parse a file containing a description of a graph.
 */
#ifndef GraphParser_Included
#define GraphParser_Included

#include "GraphTheory.h"
#include <istream>

/* Loads a graph from a stream, reporting an error if it's malformed. */
Graph loadGraph(std::istream& source);

#endif
