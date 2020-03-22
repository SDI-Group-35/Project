#ifndef POLYGONDRAW_H
#define POLYGONDRAW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPolygonItem>
#include <QContextMenuEvent>

class polygonDraw : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    polygonDraw(QPolygonF polygon, QObject *parent);

};

#endif // POLYGONDRAW_H
