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

void MainWindow::on_classDelete_clicked()
{
    delete ui -> classList -> currentItem();
}

void MainWindow::on_classAddButton_clicked()
{
    classNameField = ui->classNameField->text();
    if(classNameField.isEmpty())
        return;
    ui -> classList -> addItem(classNameField);

    names.append(classNameField);
}

//when load image button is clicked
void MainWindow::on_actionLoad_triggered()
{
    pmap -> loadImg(scene);

    scene -> addItem(pmap);
}


//draws lines
void MainWindow:: drawLines(const QPointF &firstP , const QPointF &secondP)
{
    QGraphicsLineItem *lines = scene -> addLine(firstP.x(), firstP.y(), secondP.x(), secondP.y(), pen);

    pmap -> lineV.push_back(lines);
}

//draw polygon
void MainWindow:: drawPolygon(const QPolygonF &polygon)
{

    pointer = new polygonDraw(polygon, this);

    pointer -> setPen(pen);

    scene -> addItem(pointer);

    for (const QGraphicsLineItem* line: pmap -> lineV)
    {
        delete line;
    }

    //pointer ->setFlag(QGraphicsItem::ItemIsMovable);



    //scene->addItem(ClassName);

//    QGraphicsTextItem *classText = new QGraphicsTextItem("Sam");
//    scene->addItem(classText);
//    classText->setPos(200,10);



}

void MainWindow::removePolygon(polygonDraw *Dpoly)
{
    scene->removeItem(Dpoly);
}

void MainWindow::updateClassName(QGraphicsTextItem *CName)
{
    cout << "ClassName:" << CName <<endl;
    scene->addItem(CName);
}

void MainWindow::on_radioButton_clicked()
{
    pmap -> PolygonOn = 1;
}

void MainWindow::on_saveFile_clicked()
{
    for (int i = 0; i < names.size(); ++i){
            cout << names.at(i).toLocal8Bit().constData() << endl;
    }
}

void MainWindow::on_zoomIn_clicked()
{

}
