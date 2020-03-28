#ifndef PIXELMAP_H
#define PIXELMAP_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>
#include <QGraphicsView>
#include <QFileDialog>

class pixelmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    pixelmap(QObject *parent);

    QGraphicsView *view;

    int polygonSide = 1;

    //loading image
    void loadImg(QGraphicsScene *scene);
    void ShowContextMenu(const QPoint &pos);

    void clearVectors();

    QVector <QGraphicsLineItem*> lineV;

    int PolygonOn = 0;
    int setContextMenuPolicy;

signals:
    //drawing first point to second piont
    void drawLines(QPointF , QPointF);
    void drawPolygon(QPolygonF);




protected:

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
private:
    //storing coorindates
    QVector<QPointF> xyPress;

};
#endif // PIXELMAP_H
