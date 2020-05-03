#ifndef GraphInternal_Included
#define GraphInternal_Included

#include "GraphTheory.h"

#include <string>

/* Type representing an actual node in the graph. This is abstracted away from
 * the client code so that they don't overtrain on implementation details.
 */
struct RealNode {
    std::string name;
};

/* A real color is just an RGB triplet. */
struct RealColor {
    int r, g, b;

    RealColor darker() const;
    std::string toString() const;
};

#endif
