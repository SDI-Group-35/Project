#include "polygonDraw.h"

polygonDraw::polygonDraw(QPolygonF polygon, QObject *parent):QGraphicsPolygonItem(polygon)
{
    //QWidget *widget = new QWidget;


    setFlag(QGraphicsItem::ItemIsMovable);
    //contextMenu.addAction("Copy", this, SLOT(copyPolygon()));
    contextMenu.addAction("Delete", this, SLOT(deletePolygon()));

    //connect(this, SIGNAL(dulicatePoly(QPolygonF)), parent, SLOT(polygonDraw(QPolygonF)));
    connect(this, SIGNAL(deletePoly(polygonDraw *)), parent , SLOT(deletePoly(polygonDraw *)));

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
    emit deletePoly(this);
}

void polygonDraw::copyPolygon()
{

}
