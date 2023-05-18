#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

//    //creating a scene
//    QGraphicsScene* scene =new QGraphicsScene() ;

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
