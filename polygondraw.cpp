#include "polygonDraw.h"
#include "mainwindow.h"

using namespace std;

polygonDraw::polygonDraw(QPolygonF polygon, QObject *parent):QGraphicsPolygonItem(polygon) /*when rightclicking on a Polygon a contextMenu show*/
{
    setFlag(QGraphicsItem::ItemIsMovable); /*Polygon is movable*/

    contextMenu.addAction("Copy", this, SLOT(copyPolygon())); /*adding contextMenu */
    connect(this, SIGNAL(dulicatePoly(QPolygonF)), parent, SLOT(drawPolygon(QPolygonF))); /*connecting contextMenu to the Application*/

    contextMenu.addAction("Delete", this, SLOT(deletePolygon())); /*adding contextMenu */
    connect(this, SIGNAL(removePolygon(polygonDraw *)), parent , SLOT(removePolygon(polygonDraw *))); /*connecting contextMenu to the Application*/

    contextMenu.addAction("Add Class Tag", this, SLOT(addClassTag())); /*adding contextMenu */
    connect(this, SIGNAL(updateClassName(QGraphicsTextItem *)), parent , SLOT(updateClassName(QGraphicsTextItem *))); /*connecting contextMenu to the Application*/
}

QGraphicsTextItem *polygonDraw::retrieveClassName() /*setup annotation*/
{
    ClassName = new QGraphicsTextItem("",this); /*initialising annotation tag */
    return ClassName;
}


void polygonDraw::getPolygonPos()
{
    newPoly = this->polygon(); /*stores the selected Polygon*/

    QPointF PolyPoint(0,0); /*initialising new Polygon*/

    for(int i = 0; i<newPoly.size(); i++){ /*for each point */

        if(PolyPoint.x() < newPoly.at(i).x() && PolyPoint.y() < newPoly.at(i).y()) /*compares the Polygons to find lowest Postion*/
        {
            PolyPoint.setX(newPoly.at(i).x()); /*find and set X Position*/
            PolyPoint.setY(newPoly.at(i).y()); /*find and set Y Position*/
        }
    }
    this->ClassName->setPos(PolyPoint);  /*Set QGraphicsTextItem new postion*/
}


void polygonDraw::mousePressEvent(QGraphicsSceneMouseEvent *event) /*display context Menu*/
{
    if(event->button() & Qt::RightButton) /*checks if user right clicks over a Shape*/
    {
        contextMenu.exec(event->screenPos()); /*display contextMenu on QGraphicsScene*/
    }
}


void polygonDraw::deletePolygon() /*Remove Selected Shape*/
{
    emit removePolygon(this); /*passes the polygon the user wishes to remove from the QGraphicsScene*/
    delete ClassName; /*deletes the annotation under the selected Polygon*/
}

void polygonDraw::addClassTag() /*looks for postion and name of annotation*/
{
    retrieveClassName(); /*get annotation name*/
    getPolygonPos(); /*get slected Polygon postion*/
    emit updateClassName(ClassName); /*update and displays annotation tag*/
}

void polygonDraw::copyPolygon() /*Copy Polygon*/
{
    QPolygonF copyPoly = mapToScene(polygon()); /*Makes a copy polygon and returns polygon coordinate point mapped to scene coordinates */

    for(int i = 0; i < copyPoly.size(); i++)
    {
        P = copyPoly.at(i); /*Get a point from original Polygon and load into copyPoly*/

        P.setX(P.x() + 50); /*sets new polygon Coordinate and add 50 (Prevents Polygon from stacking over eachother)*/
        P.setY(P.y() + 50); /*sets new polygon Coordinate and add 50 (Prevents Polygon from stacking over eachother)*/

        newPolyPoints.push_back(P); /*Adds copy Polygon Coordinate into the QVector*/
    }

    QPolygonF movedPoly(newPolyPoints); /*loads copy Polygon Coordinate into a QPointF to pass through before drawing*/
    emit dulicatePoly(movedPoly); /*Draws copy polygon*/
}


