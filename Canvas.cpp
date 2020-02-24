#include <iostream>
using namespace std;

#include <Canvas.h>
#include "windowsize.h"

//initialization the canvas
Canvas::Canvas(MainWindow *p) : QWidget()
{
    //initialization variables
    parent = p;
    xMax = 500;
    yMax = 500;
    label = new QLabel(this);

    //add new QPixmap with paramters at end of the Array "pixmapList"
    pixmapList.push_back(new QPixmap(xMax,yMax));
    //storing previous Array value in variable pixCurrent
    pixCurrent = pixmapList.size()-1;
    //Fills the pixmap with the given color (White).
    pixmapList[pixCurrent]->fill();
    //Constructs a painter
    painter = new QPainter(pixmapList[pixCurrent]);

    //loads the canvas, setPixmap this property holds the label's pixmap
    label->setPixmap(*pixmapList[pixCurrent]);
}



//EventMouseEvent is called whenever the mouse moves while a mouse button is held down.
void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(parent->getRectangleEnable())
    {
        //pos() returns the position of the mouse cursor
        //x() Returns the x position of the mouse cursor
        xMove = event->pos().x();
        //pos() returns the position of the mouse cursor
        //y() Returns the y position of the mouse cursor
        yMove = event->pos().y();
        //Call Function
        drawTemporaryRectangle();
    }
}

//mousePressEvent is called when a mouse button is pressed while the mouse cursor is inside the widget,
void Canvas::mousePressEvent(QMouseEvent* event)
{
    if(parent->getRectangleEnable())
    {
        //pos() returns the position of the mouse cursor
        //x() Returns the x position of the mouse cursor
        xPress = event->pos().x();
        //pos() returns the position of the mouse cursor
        //y() Returns the y position of the mouse cursor
        yPress = event->pos().y();

    }
}

//mouseReleaseEvent is called when a mouse button is released.
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(parent->getRectangleEnable())
    {
        //pos() returns the position of the mouse cursor
        //x() Returns the x position of the mouse cursor
        xRelease = event->pos().x();
        //pos() returns the position of the mouse cursor
        //y() Returns the y position of the mouse cursor
        yRelease = event->pos().y();
        //Call Function
        drawRectangle();

    }
}
//Shape Functions
void Canvas::drawRectangle()
{
    //The QPen class defines how a QPainter should draw lines and outlines of shapes.
    QPen pen;
    //add new QPixmap with paramters at end of the Array "pixmapList"
    pixmapList.push_back(new QPixmap(xMax,yMax));
    //go to current Array value in variable pixCurrent
    pixCurrent = pixCurrent+1;
    //Assigns the given pixmap to this pixmap and returns a reference to this pixmapList.
    pixmapList[pixCurrent]->operator =(*pixmapList[pixCurrent-1]);
    //Ends Qpainter, Any resources used while painting are released.
    painter->end();
    //remove Qpainter
    delete painter;
    //reassign new Qpainter to current
    painter = new QPainter(pixmapList[pixCurrent]);

    //Sets the painter's pen to be the given pen.
    //The pen defines how to draw lines.
    painter->setPen(pen);
    //Draws the current rectangle with the current X & Y postions.
    painter->drawRect(xPress,yPress,xRelease-xPress,yRelease-yPress);
    label->setPixmap(*pixmapList[pixCurrent]);
    //printCoordinates();
}
void Canvas::drawTemporaryRectangle()
{
    //The QPen class defines how a QPainter should draw lines and outlines of shapes.
    QPen pen;
    //add new QPixmap with paramters at end of the Array "pixmapList"
    pixmapList.push_back(new QPixmap(xMax,yMax));
    //go to current Array value in variable pixCurrent
    pixCurrent = pixCurrent+1;
    //Assigns the given pixmap to this pixmap and returns a reference to this pixmapList.
    pixmapList[pixCurrent]->operator =(*pixmapList[pixCurrent-1]);
    //Ends Qpainter, Any resources used while painting are released.
    painter->end();
    //remove Qpainter
    delete painter;
    //reassign new Qpainter to current
    painter = new QPainter(pixmapList[pixCurrent]);

    //Sets the painter's pen to be the given pen.
    //The pen defines how to draw lines.
    painter->setPen(pen);
    //Draws the current rectangle with the current X & Y postions.
    painter->drawRect(xPress,yPress,xMove-xPress,yMove-yPress);
    label->setPixmap(*pixmapList[pixCurrent]);
    pixmapList.remove(pixCurrent);
    pixCurrent = pixmapList.size()-1;

}

//Function slots
void Canvas::saveCanvas()
{
    //Save Canvas
    QString file = QFileDialog::getSaveFileName(0, "Save image", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    pixmapList[pixCurrent]->save(file);
}

void Canvas::openCanvas()
{
    QString file = QFileDialog::getOpenFileName(0,"Open image",QString(),"Images (*.png *.gif *.jpg *.jpeg)");
    painter->end();
    delete painter;
    pixmapList.remove(pixCurrent);
    pixmapList.push_back(new QPixmap(file));
    painter = new QPainter(pixmapList[pixCurrent]);
    label->setPixmap(*pixmapList[pixCurrent]);
}

//undo (Update Canvas)
void Canvas::newCanvas()
{
    painter->end();
    delete painter;
    pixmapList.erase(pixmapList.begin(),pixmapList.end());
    delete label;


    pixmapList.push_back(new QPixmap(xMax,yMax));
    pixCurrent = pixmapList.size()-1;
    pixmapList[pixCurrent]->fill();

    label = new QLabel(this);
    label->setPixmap(*pixmapList[pixCurrent]);
    label->show();
    painter = new QPainter(pixmapList[pixCurrent]);
}

//update canvas
void Canvas::returnCanvas()
{
    if(pixCurrent ==0) return;
    pixmapList.remove(pixCurrent);
    pixCurrent = pixmapList.size()-1;
    painter->end();
    delete painter;
    painter = new QPainter(pixmapList[pixCurrent]);
    label->setPixmap(*pixmapList[pixCurrent]);
}

//void Canvas::printCoordinates()
//{
//    cout << "Corrdinates" <<endl;
//    cout << xPress <<endl;
//    cout << yPress <<endl;
//    cout << xRelease-xPress <<endl;
//    cout << yRelease-yPress <<endl;

//}
