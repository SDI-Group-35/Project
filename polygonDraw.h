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

class MainWindow;

class polygonDraw : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:
    polygonDraw(QPolygonF polygon, QObject *parent);
    void updateClassValue(QGraphicsTextItem *value);
    QGraphicsTextItem *retrieveClassName();
    void getPolygonPos();
    QVector<QPointF> newPolyPoints;
    QPointF P;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void copyPolygon();
    void deletePolygon();
    void addClassTag();

signals:
    void dulicatePoly(QPolygonF);
    void removePolygon(polygonDraw *);
    void updateClassName(QGraphicsTextItem *);

private:
    QMenu contextMenu;

    QGraphicsTextItem *ClassName;

    /* Annotation Variable */
    QPolygonF newPoly;
    QPointF PolyPoint;

    MainWindow *mMain;


};

#endif // POLYGONDRAW_H
