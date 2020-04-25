/* If you so choose, you can write your own implementation of the "This" and "That"
 * formulas from this problem to help aid in testing. This is NOT required and you
 * can completely skip this step if you'd like.
 */

#ifndef ThisButNotThat_Included
#define ThisButNotThat_Included

#include <set>

/* Type: Person
 *
 * An opaque type representing a person.
 */
using Person = struct RealPerson*;

/* These are provided to you. You don't need to implement them. */
bool happy(Person p);
bool loves(Person x, Person y);

/* OPTIONALLY implement these functions. */
bool this_partI(std::set<Person> P);
bool that_partI(std::set<Person> P);

/* OPTIONALLY implement these functions. */
bool this_partII(std::set<Person> P);
bool that_partII(std::set<Person> P);

/* OPTIONALLY implement these functions. */
bool this_partIII(std::set<Person> P);
bool that_partIII(std::set<Person> P);

/* OPTIONALLY implement these functions. */
bool this_partIV(std::set<Person> P);
bool that_partIV(std::set<Person> P);

/* OPTIONALLY implement these functions. */
bool this_partV(std::set<Person> P);
bool that_partV(std::set<Person> P);

#endif
