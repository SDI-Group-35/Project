#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pixelmap.h"
#include "polygonDraw.h"
#include "linkedlist.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDialog>
#include <QFile>
#include <QFileSystemModel>
#include <QTextStream>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QModelIndex>
#include <QListWidget>
#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QGraphicsLineItem>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>
#include <QInputDialog>
#include <QLineEdit>




#include <QListView>

class linkedList;

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

    QString FolderPath;
    QString imageName;
    QString fileName;
    int Switch;

    QVector<QPolygonF> savePolygon;
    QJsonArray coordArray;
    QJsonObject coordObject;
    QJsonObject object;
    int Sides=0;


    QString getAnnotationName(){return annotationName;}
    QString annotationName = "No Class selected";

public slots:
    void drawLines(const QPointF &firstP , const QPointF &secondP);
    void drawPolygon(const QPolygonF &polygon);
    void removePolygon(polygonDraw *Dpoly);
    void updateClassName(QGraphicsTextItem *CName);

protected:

private slots:

    void on_polyShape_clicked();

    void on_pushButton_clicked();

    void on_WidgetImgList_currentItemChanged(QListWidgetItem *current);

    void on_loadClass_clicked();

    void on_addClass_clicked();

    void loadImage(QString fileName);

    void on_imgSortAsc_clicked();

    void on_imgSortDesc_clicked();

    void on_classSortAsc_clicked();

    void on_classSortDesc_clicked();

    void on_searchButton_clicked();

    void getSearchName();

    void searchN(QString SearchN);

    void on_deleteClass_clicked();

    void on_saveClass_clicked();

    void on_pushButton_5_clicked();

    void on_classList_currentTextChanged(const QString &currentText);

private:
    Ui::MainWindow *ui;

    linkedList *lList;

    polygonDraw *pointer;

    pixelmap * pmap;

    /* Library for image/shapes */
    QGraphicsScene * scene;

    QGraphicsPixmapItem *image;

    /* Able to draw lines */
    QPen pen;

    QStringList names;

    QStringListModel *model;


    QFileSystemModel *dirmodel;

    QFileSystemModel *filemodel;

    QString classFile;

    QString classNameFile;

};
#endif // MAINWINDOW_H
