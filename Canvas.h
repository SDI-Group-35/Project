#ifndef CANVAS_H
#define CANVAS_H

#include <QtWidgets>
#include <mainwindow.h>

class Canvas : public QWidget
{
    Q_OBJECT

public :
    Canvas(MainWindow *p); //p is the value of p while *p is the value stored in the memory location pointed by p.
    void drawRectangle();
    void drawTemporaryRectangle();
    void drawPolygon();
    void drawTemporaryPolygon();

    void printCoordinates();

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
    void newCanvas();
    void saveCanvas();
    void openCanvas();
    void returnCanvas();

private :
    int xMove;
    int yMove;
    int xPress;
    int yPress;
    int xRelease;
    int yRelease;

    int xCoordinates;
    int yCoordinates;
    int firstPx;
    int firstPy;
    int secondPx;
    int secondPy;
    int startPx;
    int startPy;

    int pixCurrent;
    int xMax;
    int yMax;

    QPainter *painter;
    QLabel *label; //QLabel is used for displaying text or an image.
    MainWindow *parent;
    QVector<QPixmap*> pixmapList; //displayed images
    //The QPixmap class is an off-screen image representation that can be used as a paint device
};

#endif // CANVAS_H
