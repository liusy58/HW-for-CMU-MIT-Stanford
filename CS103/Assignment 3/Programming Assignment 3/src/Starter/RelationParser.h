/**
 * File: RelationParser.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Exports functions needed to parse a file containing a description of a relation.
 */
#ifndef RelationParser_Included
#define RelationParser_Included

#include "BinaryRelations.h"
#include <istream>

/* Loads a binary relation from a stream, reporting an error if it's malformed. */
Relation loadRelation(std::istream& source);

#endif
