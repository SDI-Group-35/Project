#include "windowsize.h"


//int WindowSize::length = 500;
//int WindowSize::height = 500;

//WindowSize::WindowSize(Canvas *canvas) : QWidget()
//{

//    QVBoxLayout *layout = new QVBoxLayout(this);
//    lengthLine = new QLineEdit;
//    heightLine = new QLineEdit;
//    QFormLayout *given = new QFormLayout;

//    given->addRow("Enter the length (x)",lengthLine);
//    given->addRow("Enter height (y)",heightLine);


//    create = new QPushButton("Create");
//    layout->addLayout(given);
//    layout->addWidget(create);
//    connect(create,SIGNAL(clicked(bool)),canvas,SLOT(newCanvas()));
//    connect(lengthLine,SIGNAL(textChanged(QString)),this,SLOT(getLengthLine(QString)));
//    connect(heightLine,SIGNAL(textChanged(QString)),this,SLOT(getHeightLine(QString)));

//    connect(create,SIGNAL(clicked(bool)),this,SLOT(close()));
//}

//void WindowSize::createClick()
//{

//    this->show();

//}

//Functions slots
//void WindowSize::getLengthLine(QString lLine)
//{
//    //convert string (lLine) to int and stored in varaible length
//    length = lLine.toInt();
//}
//void WindowSize::getHeightLine(QString hLine)
//{
//    height = hLine.toInt();
//}

//Functions
//int WindowSize::getLength()
//{
//    return length;
//}

//int WindowSize::getHeight()
//{
//    return height;
//}
