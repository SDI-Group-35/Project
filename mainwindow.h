#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pixelmap.h"
#include "polygonDraw.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////
#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////

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
    QString classNameField;

public slots:
    void drawLines(const QPointF &firstP , const QPointF &secondP);
    void drawPolygon(const QPolygonF &polygon);
    void removePolygon(polygonDraw *Dpoly);
    void updateClassName(QGraphicsTextItem *CName);
    void on_classAddButton_clicked();
    void on_classDelete_clicked();    

protected:

   /* Save and Load Classes  start*/
    void saveToFile();
    void loadFromFile();

    QPushButton *loadButton;
    QPushButton *saveButton;

    /* Save and Load Classes end*/



private slots:

    void on_actionLoad_triggered();

    void on_radioButton_clicked();

    void on_saveFile_clicked();


    void on_pushButton_4_clicked();

    ////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();
    ////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////

private:
    Ui::MainWindow *ui;

    polygonDraw *pointer;

    pixelmap * pmap;

    //library for image/shapes
    QGraphicsScene * scene;

    //Able to draw lines
    QPen pen;

    QStringList names;


    ////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////
    QStringListModel *model;
    ////////////////////////// NEW CLASS LIST ////////////////////////// MODEL BASED //////////////////////////

};
#endif // MAINWINDOW_H
