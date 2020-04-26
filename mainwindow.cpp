#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygonDraw.h"
#include "linkedlist.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    setWindowTitle("Annotation Tool");
    pmap=new pixelmap(this); /*initialising pixelmap*/
    scene = new QGraphicsScene(this); /*initialising QGraphicsScene*/
    ui -> graphicsView -> setScene(scene); /*initialising graphicsView (canvas)*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: drawLines(const QPointF &firstP , const QPointF &secondP) /* Drawing temporary Lines */
{
    QGraphicsLineItem *lines = scene -> addLine(firstP.x(), firstP.y(), secondP.x(), secondP.y(), pen); /*draws line on QGraphicsScene*/

    pmap -> lineV.push_back(lines); /*updates pixelmap and stores coordinates in QVector QGraphicsLineItem*/
}

void MainWindow:: drawPolygon(const QPolygonF &polygon) /* Drawing Polygons */
{

    pointer = new polygonDraw(polygon, this); /*initialising new polygon with coordinates given (polygon)*/

    pointer -> setPen(pen); /*drawing polygon outlines by setting the pen*/

    scene -> addItem(pointer); /*add drawn polygon to QGraphicsScene (canvas)*/

    for (const QGraphicsLineItem* line: pmap -> lineV)
    {
        delete line; /*after drawing polygon remove the temporary lines drawn before*/
    }

    savePolygon.append(polygon); /*coordinates of the polygon are passed for save to a file*/
}

void MainWindow::removePolygon(polygonDraw *Dpoly) /* Remove polygon */
{
    scene->removeItem(Dpoly); /*removes the seleted polygon from QGraphicsScene*/
}

void MainWindow::updateClassName(QGraphicsTextItem *CName) /* Update class name */
{
    CName->setPlainText(annotationName); /*loads selected annotation name onto QGraphicsTextItem*/
    scene->addItem(CName); /*Add QGraphicsTextItem (Class Name) to QGraphicsScene under Polygon*/
}


void MainWindow::on_polyShape_clicked() /* Drawing with Polygon shape */
{
    pmap -> PolygonOn = 1; /*initialising Polygon when radio button is clicked */
}

void MainWindow::on_pushButton_clicked() /* Load image */
{
    QDir directory(QFileDialog::getExistingDirectory(this, "Open a Folder", QDir::homePath())); /*browse dialog box to locate folder of images, then load folder contents to QDir class*/

    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.png" << "*.jpeg", QDir::Files); /*only load filenames with acceptable filters*/

    if(images.isEmpty()) /*if user doesnt pick a file the problem will return prevents crashing */
        return;

    else if (images.length() > 0) { /*populate WidgetImgList (QWidgetLsit) with accepted files*/
        FolderPath = directory.path(); /*store file path*/
        foreach(QString image, images) { /*reading through the file*/
            ui -> WidgetImgList -> addItem(image); /*loads just the image names to image name pane (QWidgetLsit)*/
            lList->loadList(image);   /*loads image names into Link List*/
        }
    }
//    lList->print(); display wants inside the link list
}



void MainWindow::on_WidgetImgList_currentItemChanged(QListWidgetItem *current) /*load selected image*/
{
    imageName = current->text();  /*gets selected image name i.e cat.png*/
    fileName = FolderPath + '/' + imageName; /*stitching file path and file name together*/
    loadImage(fileName); /*calls loadimage function and pass QString of selected image file path*/
}

void MainWindow::on_loadClass_clicked() /*loads class*/
{
    ui->classList->clear(); /*clears classList (QWidgetList) before loading classes prevents errors*/
    classFile = QFileDialog::getOpenFileName(this, tr("Open Class File"), "", "Class file (*.names)"); /*open file dialog and only looks for *.names files*/

    if(classFile.isEmpty()) /*if user doesnt pick a file the problem will return prevents crashing */
        return;

    else{ QFile classNameFile(classFile); /*load class data into Qfile*/
            if(!classNameFile.open(QIODevice::ReadOnly)){ /*reads class file */
            QMessageBox::information(this, "Can not to Class file", classNameFile.errorString()); /*display "can not to open class file" to user if file isnt a *.names file*/
                return;
        }

        QTextStream in(&classNameFile); /*reads file */
        ui->classList->clear(); /*clears classList (QWidgetList) before loading classes prevents errors*/
        while (!in.atEnd()){ /*read the whole file*/
            QString line = in.readLine(); /*loads each line into QString*/
            ui->classList->addItem(line); /*updates QwidgetList adding class name to class pane*/

        }
        classNameFile.close(); /*close file */
    }
}

void MainWindow::on_addClass_clicked() /*Add New Class*/
{
    QString className; /*initialising new class Name*/
    className = ui->addClassText->text(); /*Gets String inside QLineEdit (addClassText)*/
    ui->classList->addItem(className); /*Add to the QWidgetList*/
}

void MainWindow::loadImage(QString fileName) /*load image when selected*/
{
    QImage image;
    if(image.load(fileName)){/* check if filename is true*/
        scene = new QGraphicsScene; /*initialising new QGraphicsScene*/
        pmap->setPixmap(QPixmap::fromImage(image)); /*initialising new QPixmap and loads slected image from path*/
        scene->addItem(pmap); /* loads new image QGraphicsScene*/
        ui->graphicsView->setScene(scene); /* loads new image for the user to see*/
    }
}

void MainWindow::on_deleteClass_clicked() /*Delete selected Class*/
{
    delete ui->classList->currentItem(); /*removes slected class from Class pane (classList)*/
}

void MainWindow::on_saveClass_clicked()
{
        QString file_name= QFileDialog::getSaveFileName(this,tr("Save Class File"),".",tr("*.names"));
        QFile file(file_name);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this,"Error!","Could not open file for writing.");
            return;
        }
        QTextStream out(&file);
        int classes = ui->classList->count();
        for(int i = 0; i < classes; i++)
        {
            out << ui->classList->item(i)->text()+ "\n";
        }
        file.flush();
        file.close();
}

void MainWindow::searchN(QString SearchN)
{
    Switch = lList->loadSearch(SearchN); /*passing image search name to search algorithm to try and find*/

    if (Switch == 1)
    {
        ui->searchLineEdit->setText("Image Exist"); /*if image found display this */
    }
    else if (Switch == 0)
    {
       ui->searchLineEdit->setText("Image Dont Exist");  /*if image NOT found display this */
    }
}


void MainWindow::getSearchName()
{
    QString Q = ui->searchLineEdit->text();  /*Gets String inside QLineEdit (searchLineEdit)*/
    searchN(Q);
}


void MainWindow::on_searchButton_clicked()
{
    getSearchName(); /*initialise search*/
}

//Sorting functions
QStringList sorting (QListWidget* fileList,int sort){

    QStringList images;
    int size = fileList->count();

    QString temp;
    int j;
    //places current files into a list
    for (int k=0;k<size;k++){
        images.append(fileList->item(k)->text());
    }
    //when sort = 1 ascending insertion sort
    if (sort == 1){
    for (int i = 1;i<size;i++){
        temp = images[i];
        j=i;
        while(j>0 && temp<images[j-1]){
            images[j]=images[j-1];
            images[j-1]=temp;

            j--;
        }
    }
    }
    //sort = 0 meaning descending insertion sort
    else if(sort == 0){
        for (int i = 1;i<size;i++){
            temp = images[i];
            j=i;
            while(j>0 && temp>images[j-1]){
                images[j]=images[j-1];
                images[j-1]=temp;

                j--;
            }
        }
    }
    return images;
}


void MainWindow::on_imgSortAsc_clicked()
{
    int size = ui->WidgetImgList->count();

    QStringList realList;
    realList = sorting(ui->WidgetImgList,1);
    ui->WidgetImgList->clear();
    for (int i =0;i<size;i++){
        ui->WidgetImgList->insertItem(i,realList[i]);
    }
}

void MainWindow::on_imgSortDesc_clicked()
{
    int size = ui->WidgetImgList->count();

    QStringList realList;
    realList = sorting(ui->WidgetImgList,0);
    ui->WidgetImgList->clear();
    for (int i =0;i<size;i++){
        ui->WidgetImgList->insertItem(i,realList[i]);
    }
}

void MainWindow::on_classSortAsc_clicked()
{
    int size = ui->classList->count();

    QStringList realList;
    realList = sorting(ui->classList,1);
    ui->classList->clear();
    for (int i =0;i<size;i++){
        ui->classList->insertItem(i,realList[i]);
    }
}

void MainWindow::on_classSortDesc_clicked()
{
    int size = ui->classList->count();

    QStringList realList;
    realList = sorting(ui->classList,0);
    ui->classList->clear();
    for (int i =0;i<size;i++){
        ui->classList->insertItem(i,realList[i]);
    }
}

void MainWindow::on_pushButton_5_clicked()
{

     QString textFileName= QFileDialog::getSaveFileName(this,tr("Save Annotation File"),".",tr("*.json"));  /*open file dialog with *.json format to save in*/
     QFile jsonFile(textFileName);  /*load json file (textFileName) to QFile */
     jsonFile.open(QFile::WriteOnly); /* The json file is open for writing */

     object.insert("IMAGE PATH", fileName); /*Insert Json title pass image path*/

     for(int i=0;i<savePolygon.size();i++) /*Nested For loop to find Polygon point*/
     {
         Sides=savePolygon[i].count(); /*Find how many sides a Polygon has*/

         for(int j=0;j<Sides;j++)
         {
             coordObject.insert("X Axis",savePolygon[i][j].x()); /*load X Axis polygon point into JSON file*/
             coordObject.insert("Y Axis",savePolygon[i][j].y()); /*load Y Axis polygon point into JSON file*/
             coordArray.append(coordObject); /*Inserts coord at the end of the array*/
         }
         object.insert("COORD",coordArray); /*Inserts coord into the JSON array.*/

     }

     QJsonDocument jsonSave(object); /*initialising write to JSON file*/
     jsonFile.write(jsonSave.toJson()); /*writing to JSON file*/
     jsonFile.close(); /*closing the JSON file*/
}

void MainWindow::on_classList_currentTextChanged(const QString &currentText) /*set annotation name*/
{
    annotationName = currentText; /*gets selected class name i.e cat and store for annotation */
    return;
}
