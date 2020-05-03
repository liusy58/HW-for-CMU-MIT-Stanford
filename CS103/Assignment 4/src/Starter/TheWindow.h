/**
 * File: TheWindow.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Functions exporting a singleton GWindow object that's used throughout the program.
 */
#ifndef TheWindow_Included
#define TheWindow_Included

#include "gwindow.h"
#include <string>

/**
 * Returns the window used for graphics in this assignment, creating one
 * if necessary.
 *
 * @return The graphics window.
 */
GWindow& theWindow();

/**
 * Clears the display, resetting it to its default color.
 */
void clearDisplay();

#endif
