/**
 * File: SetInternal.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * The internal representation of the Object type, along with auxiliary helper types.
 *
 * You should not need to use or modify the contents of this file, though you're welcome
 * to look around a bit if you'd like!
 *
 * Internally, Objects are wrappers around a class hierarchy consisting of a base type
 * SetObject and derived types representing sets and non-sets. This representation
 * essentially models sets as trees: each set is a node, and each of its elements is
 * a child.
 *
 * Fun fact: if you study pure set theory, you can actually get a lot of mileage by
 * modeling sets as trees. Look up "complement of the axiom of infinity" for a fun
 * tour of what happens if you do this, or take Math 161!
 */
#ifndef SetInternal_Included
#define SetInternal_Included

#include "SetTheory.h"
#include "Utilities.h"

#include <string>

/* Type: SetObject
 *
 * Polymorphic base type representing a set or an object.
 */
struct SetObject {
    /* Polymorphic classes need virtual destructors. */
    virtual ~SetObject() = default;

    virtual bool isSet() const = 0;
    virtual std::set<Object> asSet() const = 0;
    virtual std::string toString() const = 0;
};

/* Type: ActualSet
 *
 * A type representing an actual set of objects.
 */
struct ActualSet: public SetObject {
    std::set<Object> theSet;

    explicit ActualSet(const std::set<Object>& s = {}) : theSet(s) {}

    virtual bool isSet() const override;
    virtual std::set<Object> asSet() const override;
    virtual std::string toString() const override;
};

/* Type: ActualObject
 *
 * A type representing an honest-to-goodness concrete non-set object.
 */
struct ActualObject: public SetObject {
    std::string name;

    explicit ActualObject(const std::string& n) : name(n) {}

    virtual bool isSet() const override;
    virtual std::set<Object> asSet() const override;
    virtual std::string toString() const override;
};

#endif
