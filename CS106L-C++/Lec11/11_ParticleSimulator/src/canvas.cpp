#include <iostream>

#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <algorithm>
#include <QCoreApplication>
#include <QObject>
#include <QSemaphore>

#include "canvas.h"
#include "particle.h"
#undef main

MyWidget& MyWidget::getInstance() {
    static MyWidget instance;
    return instance;
}


extern const int kWindowWidth = 600;
extern const int kWindowHeight = 600;
const QString kBackgroundColor = "#FFFFFF";
const QString kCircleFill = "#000000";
const QString kCircleLine = "#0d0d0d";
const QString kLineColor = "#606060";



/* global semaphore to ensure only one update call at a time.
 * Prevents overload of update calls */
QSemaphore semaphore;


void InitCanvas(Canvas & userGraph) {
    MyWidget& g = MyWidget::getInstance();
    QObject::connect(&userGraph, SIGNAL(canvUpdated(Canvas)),
                     &g, SLOT(repaint()));
}

void MyWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.fillRect(rect(), QColor(kBackgroundColor));
    if (!userCanv.points.empty()) {
        Canvas copy;
        copy.points = userCanv.points;

        auto scale = [](const Particle& a) -> Particle {
            return {a.getX()*kWindowWidth ,
                        a.getY()*kWindowHeight,
                        a.getVx(),a.getVy(),
                        a.getRadius()*(kWindowHeight + kWindowWidth)/2.0,
                        a.getMass()};
        };
        std::transform(copy.points.begin(), copy.points.end(), copy.points.begin(), scale);



        painter.setPen(QColor(kCircleLine));
        painter.setBrush(QColor(kCircleFill));
        for (Particle & n : copy.points) {

            painter.drawEllipse(n.getX() - n.getRadius(), n.getY() - n.getRadius(), 2*n.getRadius(), 2*n.getRadius());
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
    myWidget.resize(kWindowWidth, kWindowHeight);
    myWidget.show();
    qRegisterMetaType<Canvas>(); //allows use of Canvas in signals/slots
    WorkerThread x;
    x.start();
    return app.exec();
}

void Canvas::drawCanvas(Canvas &canv) {
    if (!semaphore.tryAcquire()) return;
    MyWidget& m = MyWidget::getInstance();
    m.userCanv.points = canv.points;
    emit canvUpdated(canv);
}

void DrawCanvas(Canvas& userCanv) {
    userCanv.drawCanvas(userCanv);
}
