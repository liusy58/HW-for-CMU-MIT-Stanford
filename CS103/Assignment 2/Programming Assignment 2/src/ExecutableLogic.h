#ifndef ExecutableLogic_Included
#define ExecutableLogic_Included

#include <set>

/* Type: Person
 *
 * An opaque type representing a person.
 */
using Person = struct RealPerson*;

/* These are provided to you. You don't need to implement them. */
bool happy(Person p);
bool loves(Person x, Person y);

/* You need to implement these functions. */
bool isFormulaTrueFor_partI  (std::set<Person> P);
bool isFormulaTrueFor_partII (std::set<Person> P);
bool isFormulaTrueFor_partIII(std::set<Person> P);
bool isFormulaTrueFor_partIV (std::set<Person> P);
bool isFormulaTrueFor_partV  (std::set<Person> P);
bool isFormulaTrueFor_partVI (std::set<Person> P);
bool partVI_left(std::set<Person> P,Person x);
bool partVI_right(std::set<Person> P,Person x);
#endif
