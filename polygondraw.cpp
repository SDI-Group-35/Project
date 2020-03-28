#include "polygonDraw.h"
#include "mainwindow.h"

polygonDraw::polygonDraw(QPolygonF polygon, QObject *parent):QGraphicsPolygonItem(polygon)
{
    //QWidget *widget = new QWidget;


    setFlag(QGraphicsItem::ItemIsMovable);
    //contextMenu.addAction("Copy", this, SLOT(copyPolygon()));
    contextMenu.addAction("Delete", this, SLOT(deletePolygon()));
    contextMenu.addAction("Change Tag", this, SLOT(changeClassTag()));

    //connect(this, SIGNAL(dulicatePoly(QPolygonF)), parent, SLOT(polygonDraw(QPolygonF)));
    connect(this, SIGNAL(removePolygon(polygonDraw *)), parent , SLOT(removePolygon(polygonDraw *)));
    connect(this, SIGNAL(updateClassName(QGraphicsTextItem *)), parent , SLOT(updateClassName(QGraphicsTextItem *)));
    connect(this, SIGNAL(updateClassName(QGraphicsTextItem *)), parent , SLOT(updateClassName(QGraphicsTextItem *)));

}

void polygonDraw:: setClassName(QGraphicsTextItem *){

    ClassName = new QGraphicsTextItem("tree");

}

QGraphicsTextItem *polygonDraw::getClassName()
{
    setClassName(ClassName);
    return ClassName;
}

QPointF polygonDraw::getRightPos()
{
    QPolygonF poly = this->polygon();
    QPointF edgePoint(0,0);
    for(int i = 0; i<poly.size(); i++){
        if(poly.at(i).x() > edgePoint.x() && poly.at(i).y() > edgePoint.y())
        {
            edgePoint.setX(poly.at(i).x());
            edgePoint.setY(poly.at(i).y());
        }

    }
    this->ClassName->setPos(edgePoint);
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
}

void polygonDraw::changeClassTag()
{
    getClassName();
    getRightPos();
    emit updateClassName(ClassName);
}

void polygonDraw::copyPolygon()
{

}


