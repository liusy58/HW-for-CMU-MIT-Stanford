/**
 * File: LogicVisualizer.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Functionality to display the results of test cases in a window alongside the
 * group those tests were run on.
 */

#ifndef LogicVisualizer_Included
#define LogicVisualizer_Included

#include "TestingTypes.h"

#include <map>
#include <utility>

/* Type representing a color. */
struct Color {
    unsigned r, g, b;

    Color darker() const;
    std::string toString() const;
};

/* Displays a binary relation in the main window, using the appropriate colors. */
void visualizeRelation(const TestResults& results,
                       const std::string& errorMessage,
                       const std::map<int,  Color>& objectColors,
                       const std::map<Pair, Color>& arrowColors);

#endif
