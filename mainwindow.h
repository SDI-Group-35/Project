#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pixelmap.h"
#include "polygonDraw.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

extern int draw;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int drawing = 0;

public slots:
    void drawLines(const QPointF &firstP , const QPointF &secondP);
    void drawPolygon(const QPolygonF &polygon);
    void deletePoly(polygonDraw *);

private slots:
    void on_actionLoad_triggered();

    void on_radioButton_clicked();

private:
    Ui::MainWindow *ui;
     polygonDraw *pointer;
    pixelmap * pmap;

    //library for image/shapes
    QGraphicsScene * scene;

    //Able to draw lines
    QPen pen;

};
#endif // MAINWINDOW_H
