#include "mainwindow.h"
#include <QDesktopWidget>
#include <QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    QDesktopWidget dw;
    MainWindow w;
//    int x = dw.width()*0.8;
//    int y = dw.height()*0.8;

    int x = 1024;
    int y = 768;
    w.setFixedSize(x,y);
    w.show();
    return a.exec();

}
