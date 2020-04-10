#include <iostream>

#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <algorithm>
#include <QCoreApplication>
#include <QObject>
#include <QSemaphore>

#include "SimpleGraph.h"
#undef main

MyWidget& MyWidget::getInstance() {
    static MyWidget instance;
    return instance;
}

const int kCircleRadius = 7;
const int kCircleDiameter = 2*kCircleRadius;
const int kWindowWidth = 600;
const int kWindowHeight = 600;
const QString kBackgroundColor = "#000000";
const QString kCircleFill = "#92FCFF";
const QString kCircleLine = "#0d0d0d";
const QString kLineColor = "#606060";



/* global semaphore to ensure only one update call at a time.
 * Prevents overload of update calls */

// TODO: This was 0 but breaks in Qt 5.10. Invesitgate
QSemaphore semaphore{1};


void InitGraphVisualizer(SimpleGraph & userGraph) {
    MyWidget& g = MyWidget::getInstance();
    QObject::connect(&userGraph, SIGNAL(graphUpdated(SimpleGraph)),
                     &g, SLOT(repaint()));
}

void MyWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), QColor(kBackgroundColor));
    if (!userGraph.nodes.empty()) {
        SimpleGraph copy;
        copy.nodes = userGraph.nodes;
        copy.edges = userGraph.edges;
        auto getX = [](const Node& a, const Node& b) {return a.x < b.x;};
        double maxX = std::max_element(copy.nodes.begin(), copy.nodes.end(), getX)->x;
        double minX = std::min_element(copy.nodes.begin(), copy.nodes.end(), getX)->x;

        auto getY = [](const Node& a, const Node& b) { return a.y < b.y;};
        double maxY = std::max_element(copy.nodes.begin(), copy.nodes.end(), getY)->y;
        double minY = std::min_element(copy.nodes.begin(), copy.nodes.end(), getY)->y;

        // To avoid division by zero in the one node case
        if(minX == maxX) {
            maxX += 1;
        }

        if(minY == maxY) {
            maxY += 1;
        }

        auto scale = [maxX, maxY, minX, minY](const Node& a) -> Node {
            return {(a.x - minX) *(kWindowWidth - kCircleDiameter) / (-minX + maxX) + kCircleRadius,
                    (a.y - minY) *(kWindowHeight - kCircleDiameter) / (-minY + maxY) + kCircleRadius};
        };

        std::transform(copy.nodes.begin(), copy.nodes.end(), copy.nodes.begin(), scale);

        painter.setPen(QColor(kLineColor));
        for (Edge & e : copy.edges) {
            Node start = copy.nodes[e.start];
            Node end = copy.nodes[e.end];
            painter.drawLine(start.x, start.y, end.x, end.y);
        }

        painter.setPen(QColor(kCircleLine));
        painter.setBrush(QColor(kCircleFill));
        for (Node & n : copy.nodes) {
            painter.drawEllipse(n.x - kCircleRadius, n.y - kCircleRadius, kCircleDiameter, kCircleDiameter);
        }
    }

    //last_run = QTime::currentTime();
    semaphore.release();
}

class WorkerThread : public QThread {
    void run() {
        int _userMain();
        _userMain();

    }
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MyWidget & myWidget = MyWidget::getInstance();
//    myWidget.resize(600, 600);
    myWidget.resize(kWindowWidth, kWindowHeight);
    myWidget.show();
    qRegisterMetaType<SimpleGraph>(); //allows use of SimpleGraph in signals/slots
    WorkerThread x;
    x.start();
    return app.exec();
}

void SimpleGraph::drawGraph(SimpleGraph &graph) {
    if (!semaphore.tryAcquire()) return;
    MyWidget& m = MyWidget::getInstance();
    m.userGraph.nodes = graph.nodes;
    m.userGraph.edges = graph.edges;
    emit graphUpdated(graph);
}

void DrawGraph(SimpleGraph& userGraph) {
    userGraph.drawGraph(userGraph);
}
