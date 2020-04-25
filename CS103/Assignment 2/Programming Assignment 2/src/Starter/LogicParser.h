/**
 * File: LogicParser.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Exports functions needed to parse a file containing a description of a group
 * into the group itself.
 */
#ifndef LogicParser_Included
#define LogicParser_Included

#include "LogicInternal.h"
#include <istream>

/* Loads a group from a stream, reporting an error if it's malformed. */
Group loadGroup(std::istream& source);

#endif
