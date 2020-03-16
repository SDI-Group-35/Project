#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H


#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QtWidgets>
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QLabel>

class drawingWidget : public QWidget
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT


public:
    drawingWidget(QWidget *parent = 0);

    // Handles all events
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);


    // Has the image been modified since last save
    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

public slots:

    // Events to handle
    void clearImage();
//    void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


    // Updates the scribble area where we are painting
    void paintEvent(QPaintEvent *event) override;

    // Makes sure the area we are drawing on remains
    // as large as the widget
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawRectTo(const QPoint, const QPoint);
    void updateRect(QPoint start, QPoint newPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    // Will be marked true or false depending on if
    // we have saved after a change
    bool modified;

    // Marked true or false depending on if the user
    // is drawing
    bool scribbling;


    // Holds the current pen width & color
    int myPenWidth;
    QColor myPenColor;

    // Stores the image being drawn
    QImage image;

    QRect mRect;

    QPainter painter;

    QPixmap mPix;

    bool drawStarted;


};



inline int sides = 0;
inline int loaded = 0;



#endif // DRAWINGWIDGET_H

