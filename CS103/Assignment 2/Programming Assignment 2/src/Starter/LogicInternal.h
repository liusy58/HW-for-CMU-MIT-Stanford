/**
 * File: LogicInternal.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * The internal representation of the Person type, along with auxiliary types often used
 * when talking about collections of people.
 *
 * You should not need to use these functions or types. They're for our internal use only.
 */
#ifndef LogicInternal_Included
#define LogicInternal_Included

#include "ExecutableLogic.h"

#include <string>
#include <unordered_set>
#include <unordered_map>

/* Type: RealPerson
 *
 * This is the actual type referenced by the Person alias. It's hidden because we thought it
 * would be easier for you to treat Person as an opaque type rather than as an actual collection
 * of fields.
 */
struct RealPerson {
    std::string name; // Who this person is
    bool isHappy;     // Whether they're happy

    std::unordered_set<RealPerson*> loves; // Who they love
};

/* Type: Group
 *
 * A type representing a group of people. It's a map from names to Persons (People?)
 */
using Group = std::unordered_map<std::string, Person>;

#endif
