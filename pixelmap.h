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

    //loading image
    void loadImg(QGraphicsScene *scene);
    void ShowContextMenu(const QPoint &pos);

    void clearVectors();

    QVector <QGraphicsLineItem*> lineV;

    int sides = 0;
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

/* Linked List */
class coordList{

private:
    typedef struct node{
        int data;
        node* next;
    }* nodePtr;     /* naming and function called defined as nodePtr */

    nodePtr head;
    nodePtr curr;
    nodePtr temp;

public: /* This is where to functions goes to access private data */
    coordList();
    void addNode(int addData);      /* Add a node and place a certain value in it */
    void deleteNode(int delData);   /* Whatever value is passed in here, will be searched through the list and removed */
    void printList();               /*  */
};


#endif // PIXELMAP_H
