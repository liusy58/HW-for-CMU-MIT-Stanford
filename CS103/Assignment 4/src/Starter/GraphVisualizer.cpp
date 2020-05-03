#include "GraphVisualizer.h"
#include "TheWindow.h"
#include "GraphInternal.h"
#include "gobjects.h"
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <cmath>
#include <iostream>
using namespace std;

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
        unordered_map<string, string> attributes; // Implementation-defined
        unordered_set<string> links; // What this links to.
    };

    /* A graph is just a map from names to object data. We use a map rather than an
     * unordered_map so that the order is more predictable.
     */
    using RingGraph = map<string, Object>;

    /* Converts a logical graph into a ring graph. */
    RingGraph toGraph(const Graph& graph, const map<Node, Color>& colors) {
        RingGraph result;

        /* Create the underlying objects. */
        for (auto entry: graph) {
            /* Create an object corresponding to this person. */
            Object obj;

            obj.attributes["fill"]   = colors.at(entry.first)->toString();
            obj.attributes["border"] = colors.at(entry.first)->darker().toString();

            result[entry.first->name] = obj;
        }

        /* Add the edges. */
        for (auto entry: graph) {
            auto source = entry.first;
            for (auto dest: entry.second) {
                /* Only add the edges one way. */
                if (source->name < dest->name) {
                    result[source->name].links.insert(dest->name);
                }
            }
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
    const double kObjectRadius = 20;      // Size of an object

    const double kPadding    = 10;        // Padding in the window

    const string kEdgeColor  = "#000000"; // Color of edges in the graph

    /* Given a graph, computes the window geometry for that graph. */
    Geometry geometryFor(const RingGraph& graph) {
        Geometry result;

        /* Store the window center point. */
        result.center.x = kDrawRegion.x + kDrawRegion.width / 2.0;
        result.center.y = kDrawRegion.y + kDrawRegion.height / 2.0;

        /* Determine the smaller of the two axes to get the full radius we'll use */
        double fullRadius = min(kDrawRegion.width, kDrawRegion.height) / 2.0 - kPadding;
        result.radius = fullRadius - kObjectRadius;

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

    /* Lays out the nodes in the graph. */
    void layoutGraph(RingGraph& graph, Geometry geometry) {
        int index = 0;
        for (auto& entry: graph) {
            entry.second.pt.x = geometry.center.x + cos(index * geometry.thetaStep) * geometry.radius;

            /* -sin because the coordinate system is inverted. */
            entry.second.pt.y = geometry.center.y - sin(index * geometry.thetaStep) * geometry.radius;

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

    /* Draws an arrow from one center point to another. */
    void drawEdge(Point start, Point end) {
        /* Begin by just drawing a line from the start to the end point. */
        theWindow().setColor(kEdgeColor);
        theWindow().drawLine(start.x, start.y, end.x, end.y);
    }

    /* Draws all the arcs between the different points on the screen. */
    void drawArcs(const RingGraph& graph, Geometry geometry) {
        for (const auto& entry: graph) {
            for (const string& dest: entry.second.links) {
                drawEdge(entry.second.pt, graph.at(dest).pt);
            }
        }
    }

    /* Draws a single object on the screen. */
    void drawObject(Point pt, const string& /* name */, const unordered_map<string, string>& attributes) {
        /* Draw the background oval. */
        theWindow().setColor(attributes.at("fill"));
        theWindow().fillOval(pt.x - kObjectRadius, pt.y - kObjectRadius,
                             2 * kObjectRadius, 2 * kObjectRadius);

        /* Draw the border. */
        theWindow().setColor(attributes.at("border"));
        theWindow().drawOval(pt.x - kObjectRadius, pt.y - kObjectRadius,
                             2 * kObjectRadius, 2 * kObjectRadius);
    }

    /* Draws all the arcs between the different points on the screen. */
    void drawNodes(const RingGraph& graph) {
        for (const auto& entry: graph) {
            drawObject(entry.second.pt, entry.first, entry.second.attributes);
        }
    }

    /* Draws a relation on the screen. */
    void visualizeGraph(const Graph& G, const map<Node, Color>& colors) {
        /* Convert from our format to the visualizer internal format. */
        RingGraph graph = toGraph(G, colors);

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

    const size_t kTitleFontSize = 25;
    const string kTitleColor    = "#4080FF"; // Color for the top-level title
    const string kTitleFont     = "SansSerif-" + to_string(kTitleFontSize);

    const size_t kErrorFontSize = 20;
    const string kErrorColor    = "#A04040";
    const string kErrorFont     = "Monospace-BOLD-" + to_string(kErrorFontSize);

    /* Draws a title in the results pane. */
    void drawTitle(const string& title) {
        GLabel label(title);
        label.setColor(kTitleColor);
        label.setFont(kTitleFont);

        label.setLocation(kTestRegion.x,
                          label.getFontAscent());

        theWindow().draw(&label);
    }

    /* Draws an error in the results pane. */
    void drawError(const string& title) {
        GLabel label(title);
        label.setColor(kErrorColor);
        label.setFont(kErrorFont);

        label.setLocation(kTestRegion.x,
                          kTestRegion.y + kTestRegion.height - label.getFontDescent());

        theWindow().draw(&label);
    }

    /* Calculates the sizes of the different drawing panes based on the current window size. */
    void calculatePaneSizes() {
       kTestRegion = { 0, 0, 0.3 * theWindow().getCanvasWidth(), theWindow().getCanvasHeight() };
       kDrawRegion = { 0, kTitleFontSize, theWindow().getCanvasWidth(), theWindow().getCanvasHeight() - kTitleFontSize - kErrorFontSize };
    }
}

void visualizeGraph(const Graph& g, const string& title, const string& errorMessage,
                    const map<Node, Color>& colors) {
    calculatePaneSizes();
    clearDisplay();

    drawTitle(title);
    drawError(errorMessage);
    visualizeGraph(g, colors);

    theWindow().repaint();
}
