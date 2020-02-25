#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>


class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow();
    bool getRectangleEnable();
    bool getPolygonEnable();


public slots :
    void slotRectangle();
    void slotPolygon();


private:
    bool rectangleEnable;
    bool polygonEnable;

};

#endif


//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

//class MainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();

//private:
//    Ui::MainWindow *ui;
//};
//#endif // MAINWINDOW_H
