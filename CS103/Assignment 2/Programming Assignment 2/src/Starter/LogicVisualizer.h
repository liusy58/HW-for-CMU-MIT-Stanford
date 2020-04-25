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

/* Displays the test results in the main window, along with the group that the tests
 * were run on.
 */
void visualizeResults(const TestResults& results);

#endif
