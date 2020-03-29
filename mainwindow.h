#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pixelmap.h"
#include "polygonDraw.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

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


private:
    Ui::MainWindow *ui;

    polygonDraw *pointer;

    pixelmap * pmap;

    /* Library for image/shapes */
    QGraphicsScene * scene;

    /* Able to draw lines */
    QPen pen;

    QStringList names;

    QStringListModel *model;

};
#endif // MAINWINDOW_H
