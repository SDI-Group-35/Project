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

    ClassName = new QGraphicsTextItem("Tree");

}

QGraphicsTextItem *polygonDraw::getClassName()
{
    setClassName(ClassName);
    return ClassName;
}

void polygonDraw::getPolygonPos()
{
    QPolygonF newpoly = this->polygon();

    QPointF PolyPoint(0,0);
    for(int i = 0; i<newpoly.size(); i++){

        if(PolyPoint.x() < newpoly.at(i).x() && PolyPoint.y() < newpoly.at(i).y())
        {
            PolyPoint.setX(newpoly.at(i).x());
            PolyPoint.setY(newpoly.at(i).y());
        }

    }
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

void polygonDraw::changeClassTag()
{
    getClassName();
    getPolygonPos();
    emit updateClassName(ClassName);
}

void polygonDraw::copyPolygon()
{

}


