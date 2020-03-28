#include "mainwindow.h"
#include <QDesktopWidget>
#include <QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget dw;
    MainWindow w;
    int x = dw.width()*0.8;
    int y = dw.height()*0.8;
    w.setFixedSize(x,y);
    w.show();
    return a.exec();



    w.show();
    return a.exec();

    return 0;
}
