#include "mainwindow.h"
#include "drawingWidget.h"
#include <iostream>

drawingWidget::drawingWidget(QWidget *parent)
    : QWidget(parent)
{
    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    modified = false;
    scribbling = false;
    myPenWidth = 2;
    drawStarted = false;
    myPenColor = Qt::blue;
    mPix = QPixmap(541,451);

}

// Used to load the image and place it in the widget
bool drawingWidget::openImage(const QString &fileName)
{

    // Holds the image
    QImage loadedImage;

    // If the image wasn't loaded leave this function
    if (!loadedImage.load(fileName))
        return false;
    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;

}

// Save the current image
bool drawingWidget::saveImage(const QString &fileName, const char *fileFormat)
{
    // Created to hold the image
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

// Used to change the pen color
void drawingWidget::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

// Used to change the pen width
void drawingWidget::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

// Color the image area with white
void drawingWidget::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}


// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void drawingWidget::mousePressEvent(QMouseEvent *event)
{

    if (sides > 0){
        if(sides == 4){
            scribbling = true;
            if (event->button() == Qt::LeftButton) {
                mRect.setTopLeft(event->pos());
                mRect.setBottomRight(event->pos());
            }
        }
    }
}


void drawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling){
        mRect.setBottomRight(event->pos());
    }
    update();
}


void drawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    scribbling = false;
        update();
}


void drawingWidget::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    if (scribbling){
        painter.drawPixmap(0,0,mPix);
        painter.drawRect(mRect);

        drawStarted = true;
    }
    else if (drawStarted)
    {
        QPainter tempPainter(&mPix);
       tempPainter.drawRect(mRect);
       painter.drawPixmap(0,0,mPix);
    }
 painter.end();
}


void drawingWidget::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}




void drawingWidget::resizeImage(QImage *image, const QSize &newSize)
{
    // Check if we need to redraw the image
    if (image->size() == newSize)
        return;

    // Create a new image to display and fill it with white
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    // Draw the image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
