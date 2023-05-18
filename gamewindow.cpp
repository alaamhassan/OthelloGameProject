#include "gamewindow.h"
#include "ui_gamewindow.h"


GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    //intiailizing a scene
     GameScene =new QGraphicsScene(this) ;

     ui->graphicsView->setScene(GameScene);

     QBrush GreenBrush(Qt::green);
     QPen BlackPen(Qt::black);
     BlackPen.setWidth(1);
     GameBoardRectangle =GameScene->addRect(10,10,100,100,BlackPen,GreenBrush);






//    //creating an iteam to add it to the scene
//    QGraphicsRectItem * GameBoardRect =new QGraphicsRectItem();

//    GameBoardRect->setRect(0,0,100,100) ;

//    scene->addItem(GameBoardRect);

//    //add visualization

//    QGraphicsView * Gameview =new QGraphicsView(scene);

//    //to make it visable
//    Gameview->show();



}

GameWindow::~GameWindow()
{
    delete ui;
}
