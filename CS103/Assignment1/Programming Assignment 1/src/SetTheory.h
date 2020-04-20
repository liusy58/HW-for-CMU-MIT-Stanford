#ifndef SetTheory_Included
#define SetTheory_Included

#include <set>
#include <memory>
#include <ostream>
#include<string>
#include<iostream>
/* Type: Object
 *
 * An opaque type representing an object, which can either be a set or
 * some other object.
 *
 * Please do not access the fields of this struct. Use our provided helper functions
 * to operate on Objects.
 */
struct Object {
    std::shared_ptr<const struct SetObject> impl;
    bool operator< (const Object& rhs) const;    // Needed for std::set; see Problem Set Three!

    /* You are not allowed to directly compare Objects against one another for equality.
     * If you get an error on this line, it's probably because you tried writing something
     * like
     *
     *     if (obj1 == obj2) { ... }
     *
     * If that's the case, see if you can find another way to express the idea you're working
     * with.
     */
    bool operator==(const Object& rhs) = delete;
};

/* Operator <<
 *
 * Allows you to print out an object to the console for debugging purposes. You can use it like
 * this:
 *
 *    Object obj = // ... //
 *    std::cout << "Object: " << obj << std::endl;
 */
std::ostream& operator<< (std::ostream& out, const Object& obj);

/* Given an object, returns whether that object is a set.
 *
 * For example, given an object representing the number 1,
 * this would return false. Given an object representing
 * { 1, 2, 3 }, this function would return true.
 */
bool isSet(Object o);
std::string toString(Object o);

/* Given an object that represents a set, returns a view of
 * that object as a set.
 *
 * For example, suppose you have something like this:
 *
 *    Object o = // ... something you know is a set ... //
 *
 * You could then actually see the contents of that set
 * by writing something like
 *
 *    std::set<Object> S = asSet(o);
 *
 * If you try to convert an object to a set and that object
 * isn't actually a set, this function will trigger an error.
 *
 * Here's a nice way to iterate over all the contents of an
 * Object that you know is a set:
 *
 *    Object o = // ... something you know is a set .. //
 *    for (Object x: asSet(o)) {
 *       // ... do something to x ... //
 *    }
 */
std::set<Object> asSet(Object o);

/* You need to implement these functions. */
bool isElementOf(Object S, Object T);
bool isSubsetOf(Object S, Object T);
bool areDisjointSets(Object S, Object T);
bool isSingletonOf(Object S, Object T);
bool isElementOfPowerSet(Object S, Object T);
bool isSubsetOfPowerSet(Object S, Object T);
bool isSubsetOfDoublePowerSet(Object S, Object T);
#endif
