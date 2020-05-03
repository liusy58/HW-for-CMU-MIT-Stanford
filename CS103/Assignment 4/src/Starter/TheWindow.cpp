#include "TheWindow.h"
#include <memory>
using namespace std;

namespace {
    /* Background color. */
    const string kBackgroundColor = "#FFFFFF";

    /* Size of the display window. */
    const double kDisplayWidth = 962;
    const double kDisplayHeight = 700;

    /* Clears the display by resetting it to the background color. */
    void clearDisplay(GWindow& theWindow) {
        theWindow.setColor(kBackgroundColor);
        theWindow.fillRect(0, 0,
                           theWindow.getWidth(),
                           theWindow.getHeight());
    }

    /* Creates a window that will serve as The Window. */
    GWindow makeTheWindow() {
        GWindow window(kDisplayWidth, kDisplayHeight);

        /* Turn on double-buffering to reduce flicker. */
        window.setRepaintImmediately(false);

        /* Make the window close the program when closed. */
        window.setExitOnClose(true);

        window.setWindowTitle("Graph Theory");

        /* Make it pretty. */
        clearDisplay(window);
        window.repaint();
        return window;
    }
}

GWindow& theWindow() {
    static GWindow window = makeTheWindow();
    return window;
}

void clearDisplay() {
    clearDisplay(theWindow());
}
