#include "pixelmap.h"
#include "mainwindow.h"

pixelmap::pixelmap(QObject *parent)
{
    /* connect the point together */
    connect(this, SIGNAL(drawLines(QPointF, QPointF)), parent, SLOT(drawLines(QPointF,QPointF)));
    connect(this, SIGNAL(drawPolygon(QPolygonF)), parent, SLOT(drawPolygon(QPolygonF)));
}

void pixelmap::loadImg(QGraphicsScene *) /* loads image to Pixmap */
{
    QImage image(filename);  /* load image onto QImage */
    if (true)
    {
        QPixmap *p = new QPixmap(QPixmap::fromImage(image));  /* load image onto pixmap (canvas) */
        setPixmap(*p);  /* update pixmap */
    }
}


void pixelmap::mousePressEvent(QGraphicsSceneMouseEvent * event){ /*drawing polygon line*/

    if(PolygonOn == 1){

        xyPress.push_back(event->pos()); /* getting postions and updating/storing the coordinates into the vector */

        if(xyPress.size() > 1) /* after second point is clicked */
        {
            emit drawLines(xyPress.back(), xyPress.at(xyPress.size()-2)); /* draw lines */
            polygonSide++;
        }
    }
}

void pixelmap::clearVectors(){ /*clear Vector*/

    /*preparing for new polygon*/
    xyPress.clear();
    lineV.clear();
    polygonSide = 1;
}



void pixelmap::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* ){ /* end drawing */

    if(PolygonOn == 1){
        emit drawLines(xyPress.back(), xyPress.at(xyPress.size()-2)); /* draws line from first and last point */

        QPolygonF newPoly(xyPress); /* Storing all Polygon point */

        emit drawPolygon(newPoly); /* Drawing  Polygon*/

        clearVectors(); /*wipe all coord*/
    }
}

