#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pixelmap.h"
#include "polygonDraw.h"
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


#include <QListView>

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

    void on_polyShape_clicked();


    void on_pushButton_clicked();

    void on_ImgList_currentItemChanged(const QModelIndex &index);

    void on_ImgList_itemActivated(QListWidgetItem *item);

    void on_ImgList_itemPressed(QListWidgetItem *item);

    void on_ImgList_itemDoubleClicked(QListWidgetItem *item);

    void on_ImgList_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_loadClass_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_addClass_clicked();

    void on_classList_indexesMoved(const QModelIndexList &indexes);

private:
    Ui::MainWindow *ui;

    polygonDraw *pointer;

    pixelmap * pmap;

    /* Library for image/shapes */
    QGraphicsScene * scene;

    QGraphicsPixmapItem *image;

    /* Able to draw lines */
    QPen pen;

    QStringList names;

    QStringListModel *model;

    QString currentFolder;

    QString currentFile = "";

    QFileSystemModel *dirmodel;

    QFileSystemModel *filemodel;

    QString classFile;

    QString classNameFile;


};
#endif // MAINWINDOW_H
