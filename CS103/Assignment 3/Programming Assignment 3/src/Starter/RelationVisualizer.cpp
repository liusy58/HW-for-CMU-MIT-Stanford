#include "RelationVisualizer.h"
#include "TheWindow.h"
#include "BinaryRelations.h"
#include "gobjects.h"
#include <unordered_map>
#include <map>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

/* Implementation of the Color type. */
Color Color::darker() const {
    return { 3 * r / 4, 3 * g / 4, 3 * b / 4 };
}

string Color::toString() const {
    ostringstream result;
    result << '#';

    result << hex << setw(2) << setfill('0') << r;
    result << hex << setw(2) << setfill('0') << g;
    result << hex << setw(2) << setfill('0') << b;

    return result.str();
}

namespace {
    /* Point and Vector types for doing some linear algebra */
    struct Point {
        double x;
        double y;
    };

    struct Vector {
        double dx;
        double dy;
    };

    /* Make it easy to add a point and a vector. */
    Point operator+ (const Vector& v, const Point& p) {
        return { p.x + v.dx, p.y + v.dy };
    }
    Point operator+ (const Point& p, const Vector& v) {
        return v + p;
    }

    /* Make it easy to scale a vector. */
    Vector operator* (const Vector& v, double scalar) {
        return { v.dx * scalar, v.dy * scalar };
    }
    Vector operator* (double scalar, const Vector& v) {
        return v * scalar;
    }
    Vector operator/ (const Vector& v, double scalar) {
        return v * (1.0 / scalar);
    }

    /* Vector rotation */
    Vector rotate(const Vector& v, double theta) {
        return {
            v.dx * cos(theta) - v.dy * sin(theta),
            v.dx * sin(theta) + v.dy * cos(theta)
        };
    }

    /* Window regions, used to differentiate the object space from the results space. */
    struct Region {
        double x, y;
        double width, height;
    };

    /* Regions for test results and the display area, respectively.
     * These are not constants. They're computed once the window is set up.
     * I know global variables are bad, but, well, the alternative is worse. :-)
     */
    Region kTestRegion;
    Region kDrawRegion;

    /* We abstract away from the particulars of what we're drawing. This lets us share code
     * between different projects that want to use circular drawings of items with lines
     * between them.
     */
    struct Object {
        Point pt;
        int name; // Name of this object.
        Color color; // Color of this object.
        unordered_map<int, Color> links; // What this links to.
    };

    /* A graph is just a map from names to object data. We use a map rather than an
     * unordered_map so that the order is more predictable.
     */
    using RingGraph = map<int, Object>;

    /* Converts a relation into a ring graph. */
    RingGraph toGraph(const Relation& relation,
                      const map<int,  Color>& objectColors,
                      const map<Pair, Color>& arrowColors) {
        RingGraph result;

        /* Create the underlying objects. */
        for (int elem: relation.domain) {
            /* Create an object corresponding to this person. */
            Object obj;

            obj.name  = elem;
            obj.color = objectColors.at(elem);

            result[elem] = obj;
        }

        /* Add the edges, retaining the colors. */
        for (Pair xRy: relation.r) {
            result[xRy.first].links[xRy.second] = arrowColors.at(xRy);
        }
        return result;
    }

    /* Window geometry. */
    struct Geometry {
        Point  center;
        double radius;
        double thetaStep;
    };

    /* Constants purely for the core object system. */
    const double kObjectRadius = 25;      // Size of an object

    const double kRingRadius = 25;        // Radius of a "ring" self-loop
    const double kRingOffset = 25;        // Offset from the center of a person to a ring self-loop

    const double kArrowAngle = M_PI / 4;  // Flange angle for the triangle on edge arrows
    const double kArrowSide  = 20;        // Length of one side of the arrow.

    const double kPadding    = 10;        // Padding in the window

    const string kLabelFont  = "Monospace-BOLD-16";
    const string kLabelColor = "#000000";

    /* Given a graph, computes the window geometry for that graph. */
    Geometry geometryFor(const RingGraph& graph) {
        Geometry result;

        /* Store the window center point. */
        result.center.x = kDrawRegion.x + kDrawRegion.width / 2.0;
        result.center.y = kDrawRegion.y + kDrawRegion.height / 2.0;

        /* Determine the smaller of the two axes to get the full radius we'll use */
        double fullRadius = min(kDrawRegion.width, kDrawRegion.height) / 2.0 - kPadding;

        /* The effective radius is formed by taking the full radius, then subtracting out the
         * radius of a ring arc (which gets us to the offset to the circle centers), then
         * subtracting out the ring offset (which gets us to the object centers).
         */
        result.radius = fullRadius - kRingRadius - kRingOffset;

        /* The theta step is 2pi divided by the number of nodes. */
        result.thetaStep = 2.0 * 3.1415926535 / graph.size();

        /* Edge case! If there's only a single person, put them ever so slightly off center
         * (so we don't get a zero vector when trying to compute distances).
         */
        if (graph.size() == 1) {
            result.radius = 1;
        }

        return result;
    }

    /* Constant used to rotate the layout of the graph. */
    const double kThetaOffset = -M_PI / 2;

    /* Lays out the nodes in the graph. */
    void layoutGraph(RingGraph& graph, Geometry geometry) {
        int index = 0;
        for (auto& entry: graph) {
            entry.second.pt.x = geometry.center.x + cos(index * geometry.thetaStep + kThetaOffset) * geometry.radius;

            /* -sin because the coordinate system is inverted. */
            entry.second.pt.y = geometry.center.y - sin(index * geometry.thetaStep + kThetaOffset) * geometry.radius;

            /* Step up the index. */
            index++;
        }
    }

    /* Obtains a unit vector pointing from the first point to the second. */
    Vector unitTo(Point start, Point end) {
        double dx = end.x - start.x;
        double dy = end.y - start.y;
        double magnitude = sqrt(dx * dx + dy * dy);

        return { dx / magnitude, dy / magnitude };
    }


    /* Draws a self-loop for the given circle. */
    void drawSelfLoop(Point pt, Geometry geometry, Color color) {
        Vector v = unitTo(geometry.center, pt);

        /* Extend the vector out by the offset for where self-loops go. */
        double x = pt.x + v.dx * kRingOffset;
        double y = pt.y + v.dy * kRingOffset;

        /* Draw a circle there. */
        theWindow().setColor(color.toString());
        theWindow().drawOval(x - kRingRadius, y - kRingRadius,
                             2 * kRingRadius, 2 * kRingRadius);
    }

    /* Draws an arrow from one center point to another. */
    void drawEdge(Point start, Point end, Color color) {
        /* Begin by just drawing a line from the start to the end point. */
        theWindow().setColor(color.toString());
        theWindow().drawLine(start.x, start.y, end.x, end.y);

        /* Now the fun part - drawing the arrow. First, get a vector pointing from the
         * second point back to the first.
         */
        Vector v = unitTo(end, start);

        /* Scoot out so that we're now tangent to the circle. */
        Point apex = end + v * kObjectRadius;

        /* Compute the two triangle points. */
        Point p1 = apex + rotate(v,  kArrowAngle / 2) * kArrowSide;
        Point p2 = apex + rotate(v, -kArrowAngle / 2) * kArrowSide;

        /* Fill a polygon there. */
        GPolygon triangle;
        triangle.addVertex(apex.x, apex.y);
        triangle.addVertex(p1.x, p1.y);
        triangle.addVertex(p2.x, p2.y);
        triangle.setFilled(true);
        triangle.setColor(color.toString());
        theWindow().draw(&triangle);
    }

    /* Draws all the arcs between the different points on the screen. */
    void drawArcs(const RingGraph& graph, Geometry geometry) {
        for (const auto& entry: graph) {
            for (const auto& dest: entry.second.links) {
                /* Self-loops are drawn differently than intra-person loops. */
                if (dest.first == entry.first) {
                    drawSelfLoop(entry.second.pt, geometry, dest.second);
                } else {
                    drawEdge(entry.second.pt, graph.at(dest.first).pt, dest.second);
                }
            }
        }
    }

    /* Draws a single object on the screen. */
    void drawObject(const Object& object) {
        /* Draw the background oval. */
        theWindow().setColor(object.color.toString());
        theWindow().fillOval(object.pt.x - kObjectRadius, object.pt.y - kObjectRadius,
                             2 * kObjectRadius, 2 * kObjectRadius);

        /* Draw the border. */
        theWindow().setColor(object.color.darker().toString());
        theWindow().drawOval(object.pt.x - kObjectRadius, object.pt.y - kObjectRadius,
                             2 * kObjectRadius, 2 * kObjectRadius);

        /* Draw the label. The only attribute is the name. */
        GLabel label(to_string(object.name));
        label.setFont(kLabelFont);
        label.setColor(kLabelColor);
        label.setLocation(object.pt.x - label.getWidth() / 2.0,
                          object.pt.y + label.getFontAscent() / 2.0);
        theWindow().draw(&label);
    }

    /* Draws all the arcs between the different points on the screen. */
    void drawNodes(const RingGraph& graph) {
        for (const auto& entry: graph) {
            drawObject(entry.second);
        }
    }

    /* Draws a relation on the screen. */
    void visualizeRelation(const Relation& relation,
                           const map<int,  Color>& objectColors,
                           const map<Pair, Color>& arrowColors) {
        /* Convert from our format to the visualizer internal format. */
        RingGraph graph = toGraph(relation, objectColors, arrowColors);

        /* If there are no people in the group, there's nothing to do. We avoid some
         * edge cases by not messing around with this case.
         */
        if (!graph.empty()) {
            /* Compute the window geometry that we'll use for this graph. */
            Geometry geometry = geometryFor(graph);

            /* Position all points in the graph. */
            layoutGraph(graph, geometry);

            drawArcs(graph, geometry);
            drawNodes(graph);
        }
    }

    const string kTestBorderColor = "#808080";

    /* Draws a border on the side of the test area. */
    void drawBorder() {
        theWindow().setColor(kTestBorderColor);
        theWindow().drawLine(kTestRegion.x + kTestRegion.width,
                             kTestRegion.y,
                             kTestRegion.x + kTestRegion.width,
                             kTestRegion.y + kTestRegion.height);
    }

    const string kTitleColor = "#4080FF"; // Color for the top-level title
    const int kMaxTitleSize = 26;         // Max font size for the top-level title
    const string kTitleFont = "SansSerif-";

    /* Draws a title in the results pane. */
    void drawTitle(const string& title) {
        GLabel label(title);
        label.setColor(kTitleColor);

        /* Shrink the label until it fits */
        for (int fontSize = kMaxTitleSize; fontSize > 0; fontSize--) {
            label.setFont(kTitleFont + to_string(fontSize));
            if (label.getWidth() < kTestRegion.width) break;
        }

        label.setLocation(kTestRegion.x + (kTestRegion.width - label.getWidth()) / 2,
                          label.getFontAscent());

        theWindow().draw(&label);
    }

    const double kTestCaseYOffset = 100;
    const double kTestCaseHeight  = 30;
    const double kTestCaseXOffset = 50;
    const double kBoxSize         = 0.85 * kTestCaseHeight;
    const double kBoxPadding      = 5;

    /* Struct type representing all the information necessary to color and style the
     * test results.
     */
    struct TestDisplayProperties {
        string font;
        string textColor;

        string boxColor;
        string boxText;
        string boxFont;
        string boxTextColor;
    };

    /* Map from results (TRUE, FALSE, etc.) to the info about how they're displayed. */
    const map<Result, TestDisplayProperties> kTestDisplayInfo = {
        { Result::TRUE,  { "SansSerif-16", "#000080", "#0000A0", "T", "SansSerif-BOLD-16", "#FFFFFF" } },
        { Result::FALSE, { "SansSerif-16", "#FFA010", "#FFA010", "F", "SansSerif-BOLD-16", "#FFFFFF" } },
        { Result::ERROR, { "SansSerif-ITALIC-16", "#808080", "#808080", "!", "SansSerif-BOLD-16", "#FFFFFF" } }
    };

    /* Draws the "result box" graphical icon for a given result. */
    void drawResultBox(const NamedResult& result, double initY) {
        auto properties = kTestDisplayInfo.at(result.result);

        double x = kTestRegion.x + kTestCaseXOffset;
        double y = initY + (kTestCaseHeight - kBoxSize) / 2.0;

        /* Draw the box. */
        theWindow().setColor(properties.boxColor);
        theWindow().fillRect(x, y, kBoxSize, kBoxSize);

        /* Draw the label */
        GLabel text(properties.boxText);
        text.setFont(properties.boxFont);
        text.setColor(properties.boxTextColor);

        text.setLocation(x + (kBoxSize - text.getWidth()) / 2.0,
                         y + (kBoxSize + text.getFontAscent()) / 2.0);
        theWindow().draw(&text);
    }

    /* Draws the text for a single test case result */
    void drawResultText(const NamedResult& result, double y) {
        /* Skip over the results box. */
        double x = kTestRegion.x + kTestCaseXOffset + kBoxSize + kBoxPadding;

        auto properties = kTestDisplayInfo.at(result.result);

        GLabel text(result.name);
        text.setColor(properties.textColor);
        text.setFont(properties.font);

        text.setLocation(x, y + (kTestCaseHeight + text.getFontAscent()) / 2.0);
        theWindow().draw(&text);
    }

    /* Draws a single test case result. */
    void drawOneResult(const NamedResult& result, double y) {
        drawResultBox(result, y);
        drawResultText(result, y);
    }

    /* Draws each individual test case result. */
    void drawIndividualResults(const vector<NamedResult>& results) {
        for (size_t i = 0; i < results.size(); i++) {
            drawOneResult(results[i], kTestCaseYOffset + kTestRegion.y + kTestCaseHeight * i);
        }
    }

    /* Given a file name, strips the extension off of the file. */
    string stripSuffixFrom(const string& input) {
        auto firstDot = input.find('.');

        /* There may be no suffix, and that's okay! */
        if (firstDot == string::npos) return input;

        return input.substr(0, firstDot);
    }

    /* Displays the results of the test cases. */
    void displayResults(const TestResults& results) {
        drawBorder();
        drawTitle(stripSuffixFrom(results.name));
        drawIndividualResults(results.results);
    }

    const size_t kErrorFontSize = 20;
    const string kErrorColor    = "#A04040";
    const string kErrorFont     = "Monospace-BOLD-" + to_string(kErrorFontSize);

    /* Calculates the sizes of the different drawing panes based on the current window size. */
    void calculatePaneSizes() {
       /* Both panes are designed to have a buffer to let the error message show. */
       kTestRegion = { 0, 0, 0.3 * theWindow().getCanvasWidth(), theWindow().getCanvasHeight() - kErrorFontSize };
       kDrawRegion = { kTestRegion.width, kTestRegion.y, theWindow().getCanvasWidth() - kTestRegion.width, kTestRegion.height };
    }

    /* Draws an error message on the screen. */
    void displayError(const string& error) {
        GLabel label(error);
        label.setColor(kErrorColor);
        label.setFont(kErrorFont);

        label.setLocation(0, theWindow().getCanvasHeight() - label.getFontDescent());

        theWindow().draw(&label);
    }
}

void visualizeRelation(const TestResults& results,
                       const string& errorMessage,
                       const map<int,  Color>& objectColors,
                       const map<Pair, Color>& arrowColors) {
    calculatePaneSizes();
    clearDisplay();

    visualizeRelation(results.relation, objectColors, arrowColors);
    displayResults(results);
    displayError(errorMessage);

    theWindow().repaint();
}
