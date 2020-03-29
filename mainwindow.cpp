#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygonDraw.h"
#include <iostream>
#include <QGraphicsLineItem>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    pmap=new pixelmap(this);
    scene = new QGraphicsScene(this);
    ui -> graphicsView -> setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Adds classes to classList */
void MainWindow::on_classAddButton_clicked()
{
    classNameField = ui->classNameField->text();
    if(classNameField.isEmpty())
        return;
    ui -> classList -> addItem(classNameField);

    names.append(classNameField);
}


/* Delets classes from classList */
void MainWindow::on_classDelete_clicked()
{
    delete ui -> classList -> currentItem();
}

/* Load image button is clicked */
void MainWindow::on_actionLoad_triggered()
{
    pmap -> loadImg(scene);

    scene -> addItem(pmap);
}


/* Drawing Lines */
void MainWindow:: drawLines(const QPointF &firstP , const QPointF &secondP)
{
    QGraphicsLineItem *lines = scene -> addLine(firstP.x(), firstP.y(), secondP.x(), secondP.y(), pen);

    pmap -> lineV.push_back(lines);
}

/* Drawing Polygons */
void MainWindow:: drawPolygon(const QPolygonF &polygon)
{

    pointer = new polygonDraw(polygon, this);

    pointer -> setPen(pen);

    scene -> addItem(pointer);

    for (const QGraphicsLineItem* line: pmap -> lineV)
    {
        delete line;
    }
}

/* Remove polygon */
void MainWindow::removePolygon(polygonDraw *Dpoly)
{
    scene->removeItem(Dpoly);
}

/* Update class name */
void MainWindow::updateClassName(QGraphicsTextItem *CName)
{
    cout << "ClassName:" << CName <<endl;
    scene->addItem(CName);
}

/* Drawing with Polygon shape */
void MainWindow::on_polyShape_clicked()
{
    pmap -> PolygonOn = 1;
}
