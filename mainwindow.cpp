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
    //image = new QGraphicsPixmapItem();
    scene = new QGraphicsScene(this);
    ui -> graphicsView -> setScene(scene);


    QString sPath = "C:/";

    filemodel = new QFileSystemModel(this);
    filemodel -> setFilter(QDir::NoDotAndDotDot | QDir::Files );
    filemodel-> setRootPath(sPath);

    ui -> ImgList -> setModel(filemodel);

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
    //pmap -> loadImg(scene);

    //scene -> addItem(pmap);
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

void MainWindow::on_pushButton_clicked()
{
//    // browse dialog box to locate images folder, then load folder contents to QDir class
//    QDir directory(QFileDialog::getExistingDirectory(this, "Open a Folder", QDir::homePath()));

//    // only load filenames with acceptable image postfixes
//    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.png" << "*.jpeg", QDir::Files);

//    // populate listbox with acceptable files
//    if (images.length() > 0) {
//        // store path for later
//        currentFolder = directory.path();
//        qInfo() << currentFolder << endl;
//        foreach(QString image, images) {
//            //ui -> ImgList -> addItem(image);
//        }
//    } else
//    {
//        // show user error box if no images were found in folder
//        //QMessageBox::information(this, "ERROR", "No images found in that directory");
//    }

    QString sPath = QFileDialog::getExistingDirectory(this, tr("Choose catalog"), ".", QFileDialog::ReadOnly);
    QStringList filter;
        filter << QLatin1String(".png");
        filter << QLatin1String(".jpeg");
        filter << QLatin1String(".jpg");
        filter << QLatin1String(".gif");
        filter << QLatin1String("*.raw");
        filemodel -> setNameFilters(filter);

    ui -> ImgList -> setRootIndex(filemodel -> setRootPath(sPath));

}



void MainWindow::on_ImgList_currentItemChanged(const QModelIndex &index)
{

//    scene->removeItem(pmap);
//    // store filename ready for opening
//    currentFile = current->text();
//    qInfo() << currentFile << endl;

//    // get the filename
//    if (currentFile != " "){
//        QString path = currentFolder + currentFile;
//        qInfo() << path << " Yess " << endl;
//        QImage imagePath(path);

//          scene = new QGraphicsScene(this);
//          pmap = new pixelmap(this);

//          /* load image onto pixmap (canvas) */
//          QPixmap *p = new QPixmap(QPixmap::fromImage(imagePath));

//          scene -> addItem(pmap);




//    }
//    else
//    {
//        scene->removeItem(pmap);
//    }


//    QString sPath = filemodel -> fileInfo(index).path();

//    pmap -> filename = filemodel -> filePath(index);

//    pmap -> loadImg(scene);
//    scene -> addItem(pmap);
}

void MainWindow::on_ImgList_clicked(const QModelIndex &index)
{
    QString sPath = filemodel -> fileInfo(index).path();

    std:: cout << sPath.toStdString();

    pmap -> filename = filemodel -> filePath(index);

    pmap -> loadImg(scene);
    scene -> addItem(pmap);
}
