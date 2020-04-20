#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygonDraw.h"
#include <iostream>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QLabel>
#include <QVector>


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

    dirmodel = new QFileSystemModel(this);
    dirmodel -> setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dirmodel -> setRootPath(sPath);


    filemodel = new QFileSystemModel(this);
    filemodel -> setFilter(QDir::NoDotAndDotDot | QDir::Files );
    filemodel-> setRootPath(sPath);

    ui -> ImgList -> setModel(filemodel);


}

MainWindow::~MainWindow()
{
    delete ui;
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

    ui -> ImgList ->setRootIndex(filemodel -> setRootPath(sPath));

}

void MainWindow::on_ImgList_clicked(const QModelIndex &index)
{
    pmap -> filename = filemodel -> filePath(index);

    pmap -> loadImg(scene);
    scene -> addItem(pmap);
}

void MainWindow::on_loadClass_clicked()
{
//    QString sPath = QFileDialog::getOpenFileName(this, tr("Choose Class"), ".", tr("Text Files (*.txt))"));
//    QStringList filter2;
//    filter2<< QLatin1String("*.txt");
//    dirmodel -> setNameFilters(filter2);

//    ui -> classList -> setRootIndex(dirmodel -> setRootPath(sPath));



//    QString dPath = QFileDialog::getExistingDirectory(this, tr("Choose folder"), ".", QFileDialog::ReadOnly);
//    QStringList filter;
//    filter << QLatin1String("*.txt");;
//    dirmodel -> setNameFilters(filter);

//    ui -> classList ->setRootIndex(dirmodel -> setRootPath(dPath));

    classFile = QFileDialog::getOpenFileName(this, tr("Open Class File"), "", "Class file (*.names)");
    if(classFile.isEmpty())
        return;
    else{
        QFile classNameFile(classFile);
            if(!classNameFile.open(QIODevice::ReadOnly)){
            QMessageBox::information(this, "Can not to open file", classNameFile.errorString());
                return;
        }
        QTextStream in(&classNameFile);
        ui->classList->clear();
        while (!in.atEnd()){
            QString line = in.readLine();

            ui->classList->addItem(line);

        }
        classNameFile.close();
    }
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QModelIndex index1 = ui->classList->currentIndex();
    qInfo()<<index1<<endl;
    QString itemText = index1.data(Qt::DisplayRole).toString();
    QString filename = itemText;

    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<" Could not open the file for reading.";
        return;
    }
    QTextStream in (&file);
    QString myText = in.readAll();
    qDebug()<<myText;

    file.close();
}

void MainWindow::on_addClass_clicked()
{
    QString file_name= QFileDialog::getSaveFileName(this,tr("Save Class File"),".",tr("*.names"));
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Error!","Could not open file for writing.");
        return;
    }
    QTextStream out(&file);
    QString text = ui->classNameField->toPlainText();
    out << text;
    file.flush();
    file.close();
}


/* QInputDialog */
