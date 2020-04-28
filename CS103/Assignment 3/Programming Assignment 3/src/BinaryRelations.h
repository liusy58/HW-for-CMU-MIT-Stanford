#ifndef BinaryRelations_Included
#define BinaryRelations_Included

#include <set>
#include <vector>
#include <utility>

/* Type: Pair
 *
 * A type representing an ordered pair. This is just an alias for the built-in
 * std::pair<int, int> type. The two elements of the pair are named .first and .second,
 * so you can do something like this:
 *
 *     Pair p = { 137, 42 };
 *     p.first = 19;
 *     p.second--;
 */
using Pair = std::pair<int, int>;

/* Type: Relation
 *
 * A type representing a binary relation. Although in principle relations can be made over
 * any kind of objects, for simplicity in this assignment we'll be looking at relations
 * over integers.
 *
 * Each relation is represented by an underlying set called the domain and a set of pairs
 * defining the relation. If R is a binary relation over a set A, then the domain is the set
 * A, and R would then be expressed as the set of ordered pairs where the relation holds.
 *
 * For example, if the variable R represents a binary relation, then you can see if xRy
 * holds by testing if {x, y} is an element of R.r, like this:
 *
 *     if (R.r.count({ x, y })) {
 *         ...
 *     }
 */
struct Relation {
    std::set<int>  domain; // The set over which the relation is defined
    std::set<Pair> r;      // The set of pairs defining the relation.
};

/* Your task is to implement these predicate functions. */
bool isReflexive(Relation R);
bool isIrreflexive(Relation R);
bool isSymmetric(Relation R);
bool isAsymmetric(Relation R);
bool isTransitive(Relation R);
bool isEquivalenceRelation(Relation R);
bool isStrictOrder(Relation R);

/* You also need to implement this function to find equivalence classes. */
std::vector<std::set<int>> equivalenceClassesOf(Relation R);

/* You also should implement this function to compute covering relations. */
Relation coverOf(Relation R);

#endif
