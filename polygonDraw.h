#ifndef POLYGONDRAW_H
#define POLYGONDRAW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPolygonItem>
#include <QMenu>

#include<string>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsTextItem>
#include<QVector2D>

class polygonDraw : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    polygonDraw(QPolygonF polygon, QObject *parent);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private slots:
    //void movePolygon();
    void copyPolygon();
    void deletePolygon();

signals:
    void dulicatePoly(QPolygonF);
    void deletePoly(polygonDraw *);

private:
    QMenu contextMenu;


};

#endif // POLYGONDRAW_H
