#ifndef POLYGONDRAW_H
#define POLYGONDRAW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPolygonItem>
#include <QMenu>
#include <string>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QVector2D>

class polygonDraw : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:
    polygonDraw(QPolygonF polygon, QObject *parent);
    void setClassName(QGraphicsTextItem *value);
    QGraphicsTextItem *getClassName();
    QPointF getRightPos();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void copyPolygon();
    void deletePolygon();
    void changeClassTag();

signals:
    void dulicatePoly(QPolygonF);
    void removePolygon(polygonDraw *);
    void updateClassName(QGraphicsTextItem *);

private:
    QMenu contextMenu;

    QGraphicsTextItem *ClassName;



};

#endif // POLYGONDRAW_H
