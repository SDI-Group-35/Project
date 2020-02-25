#include "ui_mainwindow.h"

#include "mainwindow.h"
#include "Canvas.h"

MainWindow::MainWindow()
{
    resize(500,500);

    //initialization variables
    rectangleEnable = 0;
    polygonEnable = 0;

    //initialization Canvas
    // 'this' pointer points to the current object instance and passes it has a paramater to Canvas in Canvas.cpp
    Canvas *canvas = new Canvas(this);

    //initialization WindowSize with canvas (passes canvas through to WindowSize)
    //Sets the given widget (canvas) to be the main window's central widget.
    //initialization WindowSize::WindowSize(Canvas *canvas) : QWidget()
    //    WindowSize *windowSize = new WindowSize(canvas);
    setCentralWidget(canvas);

    //Create file Menu
    //using Qmenu class to provide a main menu bar by calling menuBar and then add a menu with the title name file to be displayed
    QMenu *fileMenu = menuBar()->addMenu("&File");

    //QActions are added to the menus, which display them as menu item and storing them in actionNew.
    //storing actionNew into fileMenu. The function adds the newly created action to the menu's list of actions, and returns it.
    //    QAction *actionNew = new QAction("New",this);
    //    fileMenu->addAction(actionNew);

    //QActions are added to the menus, which display them as menu item and storing them in actionSave.
    //storing actionSave into fileMenu. The function adds the newly created action to the menu's list of actions, and returns it.
    QAction *actionSave = new QAction("Save",this);
    fileMenu->addAction(actionSave);

    //QActions are added to the menus, which display them as menu item and storing them in actionOpen.
    //storing actionOpen into fileMenu. The function adds the newly created action to the menu's list of actions, and returns it.
    QAction *actionOpen = new QAction("Open",this);
    fileMenu->addAction(actionOpen);

    //connect(Sender "actionNew",SIGNAL(Value Changed),receiver of the signal "windowSize",SLOT(receivers data from windowSize)
    //Sender sends to the signal and the recevier receive the SLOT
    //    connect(actionNew,SIGNAL(triggered(bool)),windowSize,SLOT(createClick()));
    connect(actionSave,SIGNAL(triggered(bool)),canvas,SLOT(saveCanvas()));
    connect(actionOpen,SIGNAL(triggered(bool)),canvas,SLOT(openCanvas()));

    //Shapes Menu
    QMenu *shapeMenu = menuBar()->addMenu("Shapes");

    QAction *actionRectangle = new QAction("Rectangle",this);
    shapeMenu->addAction(actionRectangle);
    QAction *actionPolygon = new QAction("Polygon",this);
    shapeMenu->addAction(actionPolygon);

    connect(actionRectangle,SIGNAL(triggered(bool)),this,SLOT(slotRectangle()));
    connect(actionPolygon,SIGNAL(triggered(bool)),this,SLOT(slotPolygon()));

    //Option Menu
    QMenu *optionMenu = menuBar()->addMenu("Tools");

    QAction *actionReturn = new QAction("Go back",this);
    actionReturn->setShortcut(QKeySequence("Ctrl+Z"));
    optionMenu->addAction(actionReturn);

    connect(actionReturn,SIGNAL(triggered(bool)),canvas,SLOT(returnCanvas()));

}
//FUNCTIONS
bool MainWindow::getRectangleEnable()
{
    return rectangleEnable;
}

bool MainWindow::getPolygonEnable()
{
    return polygonEnable;
}

//SLOTS

void MainWindow::slotRectangle()
{
    rectangleEnable = 1;
}

void MainWindow::slotPolygon()
{
    polygonEnable = 1;
}


//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//}

//MainWindow::~MainWindow()
//{
//    delete ui;
//}

