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
    QString currentFolder;
    QString currentFile = "";
    QString fileName = "";

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

    void on_WidgetImgList_currentItemChanged(QListWidgetItem *current);

    void on_ImgList_itemActivated(QListWidgetItem *item);

    void on_ImgList_itemPressed(QListWidgetItem *item);

    void on_ImgList_itemDoubleClicked(QListWidgetItem *item);

    void on_ImgList_clicked(const QModelIndex &index);

    void on_loadClass_clicked();

    void loadImage(QString fileName);

    void on_classList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_addClass_clicked();

    void on_deleteClass_clicked();

    void on_saveClass_clicked();

    void on_classList_currentRowChanged(int currentRow);

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


    QFileSystemModel *dirmodel;

    QFileSystemModel *filemodel;

    QString classFile;

    QString classNameFile;

    QString annotationName;


};
#endif // MAINWINDOW_H
