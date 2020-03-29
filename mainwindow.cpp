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

////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////
    // Create model
      model = new QStringListModel(this);

      // Make data
      QStringList List;
      List << "Clair de Lune" << "Reverie" << "Prelude";

      // Populate our model
      model->setStringList(List);

      // Glue model and view together
      ui->listView->setModel(model);
      ui->comboBox->setModel(model);

      // Add additional feature so that
      // we can manually modify the data in ListView
      // It may be triggered by hitting any key or double-click etc.
      ui->listView->
              setEditTriggers(QAbstractItemView::AnyKeyPressed |
                              QAbstractItemView::DoubleClicked);
////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////


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
void MainWindow::on_pushButton_4_clicked()
{
    cout << model << endl;
}

////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////

void MainWindow::on_pushButton_2_clicked()
{
    // Add button clicked
    // Adding at the end

    // Get the position
    int row = model->rowCount();

    // Enable add one or more rows
    model->insertRows(row,1);

    // Get the row for Edit mode
    QModelIndex index = model->index(row);

    // Enable item selection and put it edit mode
    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
}

void MainWindow::on_pushButton_3_clicked()
{
    // Insert button clicked

    // Get the position
    int row = ui->listView->currentIndex().row();

    // Enable add one or more rows
    model->insertRows(row,1);

    // Get row for Edit mode
    QModelIndex index = model->index(row);

    // Enable item selection and put it edit mode
    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
}

void MainWindow::on_pushButton_7_clicked()
{
    // Delete button clicked
    // For delete operation,
    // we're dealing with a Model not a View
    // Get the position
    model->removeRows(ui->listView->currentIndex().row(),1);
}
////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////
