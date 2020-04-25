#include "ExecutableLogic.h"
#include "LogicInternal.h"

/* These functions just introspect on the internal details of the RealPerson type.
 * We provided these functions as wrappers around the internal state to simplify
 * the overall logic you needed to write.
 */
bool happy(Person p) {
    return p->isHappy;
}

bool loves(Person x, Person y) {
    return x->loves.find(y) != x->loves.end();
}
