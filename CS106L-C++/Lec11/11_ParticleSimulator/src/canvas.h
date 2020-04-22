#pragma once
#define Canvas simplegraph_temp //Hack to redefine Canvas using QT libraries

/*************************************************************************
 * File: Canvas.h
 *
 * A header file defining a set of functions which can be used to visualize a
 * simple graph.  The types declared here and the DrawGraph() function will
 * allow you to render a scaled version of a Canvas you pass in.
 */

#include <vector>
#include <cstddef>
#include <QObject>
#include <QWidget>
#include <QTime>
#include "particle.h"

/**
 * Type: Node
 * -----------------------------------------------------------------------
 * A type representing a node in a graph.  Each node stores only the x and
 * y coordinates of where the node is in the plane; all other information
 * about the node is stored implicitly by its position in the Canvas
 * list of nodes.
 */
//struct Point {
//  double x, y;  // center of point
//  double vx, vy;
//  double radius;
//  double mass;
//};

/**
 * Type: Canvas
 * -----------------------------------------------------------------------
 * A type representing a simple graph of nodes and edges.
 */

struct Canvas {
    std::vector<Particle> points;
};

/**
 * Function: DrawGraph(Canvas& graph)
 * -----------------------------------------------------------------------
 * Draws the specified graph.
 */

void DrawGraph(Canvas& userGraph);
void InitGraphVisualizer(Canvas& userGraph);




/** Implementation Details Below
 * -----------------------------------------------------------------------
 * You do not need to read anything below this point and doing so may
 * be confusing.
 */

#undef Canvas


/** Real Canvas that uses Q_OBJECT Macro */
class Canvas : public QObject {
  Q_OBJECT

  public:
    Canvas(){}
    Canvas(const Canvas& other):QObject(), points(other.points) {}
    std::vector<Particle> points;

    void drawCanvas(Canvas & graph);

  signals:
    void canvUpdated(Canvas graph);
};

void DrawCanvas(Canvas& userGraph);
void InitCanvas(Canvas& userGraph);

Q_DECLARE_METATYPE(Canvas) //allows use of Simplegraph in signals/slots

class MyWidget : public QWidget {
    Q_OBJECT
public:
    static MyWidget & getInstance();
//    void initGraph(Canvas & userCanv);        TODO: why is this here

protected:
    void paintEvent(QPaintEvent *event);

private:
    Canvas userCanv;
    QTime last_run;
    friend void Canvas::drawCanvas(Canvas & canv);

};

/** Redefinition: main
 * -----------------------------------------------------------------------
 * Due to a quirk in the way that the QT graphics works, main
 * actually must be in the graphics module itself.  This macro redefines
 * main to some other harmless term so that in your implementation, you
 * can define main but have it really invoked by the graphics driver.
 * This is a fairly unpleasant hack, but it's necessary.
 */
#define main _userMain
