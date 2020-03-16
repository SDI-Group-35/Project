#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QList>
#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QPainter>
#include <QGraphicsItem>
#include <QtGui>
#include <QMouseEvent>
#include <QtWidgets>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



protected:


private slots:





    void on_radioButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();

    bool maybeSave();

    bool saveFile(const QByteArray &fileFormat);


    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *openAct;

    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

class CustomItem : public QGraphicsRectItem
{
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        qDebug() << "Custom item clicked.";
    }
};


#endif // MAINWINDOW_H
