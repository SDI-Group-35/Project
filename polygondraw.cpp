#include "polygonDraw.h"
#include "mainwindow.h"

polygonDraw::polygonDraw(QPolygonF polygon, QObject *parent):QGraphicsPolygonItem(polygon)
{
    //QWidget *widget = new QWidget;


    setFlag(QGraphicsItem::ItemIsMovable);
    //contextMenu.addAction("Copy", this, SLOT(copyPolygon()));
    contextMenu.addAction("Delete", this, SLOT(deletePolygon()));
    contextMenu.addAction("Add Class Tag", this, SLOT(addClassTag()));

    //connect(this, SIGNAL(dulicatePoly(QPolygonF)), parent, SLOT(polygonDraw(QPolygonF)));
    connect(this, SIGNAL(removePolygon(polygonDraw *)), parent , SLOT(removePolygon(polygonDraw *)));
    connect(this, SIGNAL(updateClassName(QGraphicsTextItem *)), parent , SLOT(updateClassName(QGraphicsTextItem *)));
}

void polygonDraw:: updateClassValue(QGraphicsTextItem *){

    ClassName = new QGraphicsTextItem("Tree");

}

QGraphicsTextItem *polygonDraw::retrieveClassName()
{
    updateClassValue(ClassName);
    return ClassName;
}

void polygonDraw::getPolygonPos()
{
    //stores the selected Polygon
    newPoly = this->polygon();

    QPointF PolyPoint(0,0);

    for(int i = 0; i<newPoly.size(); i++){

        //compares the Polygons to find the Postion
        if(PolyPoint.x() < newPoly.at(i).x() && PolyPoint.y() < newPoly.at(i).y())
        {
            //set new Position
            PolyPoint.setX(newPoly.at(i).x());
            PolyPoint.setY(newPoly.at(i).y());
        }

    }
    //update Position
    this->ClassName->setPos(PolyPoint);
}


void polygonDraw::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() & Qt::RightButton)
    {
        contextMenu.exec(event->screenPos());

    }
}


void polygonDraw::deletePolygon()
{
    emit removePolygon(this);
    delete ClassName;
}

void polygonDraw::addClassTag()
{
    retrieveClassName();
    getPolygonPos();
    emit updateClassName(ClassName);
}

void polygonDraw::copyPolygon()
{

}


