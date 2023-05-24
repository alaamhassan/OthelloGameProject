#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QGraphicsView>
#include<QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    gameBoard =new GameBoard();



    ui->graphicsView->setScene(gameBoard->GetBoardScene());

    ui->graphicsView->setMouseTracking(true);
    setMouseTracking(true);
    qDebug()<<"mouse:"<<(ui->graphicsView->hasMouseTracking());

    ui->graphicsView->show();



}

GameWindow::~GameWindow()
{
delete ui;
}

//void mousePressEvent(QGraphicsSceneMouseEvent *e)
//{
//qDebug() << "You clicked ";
////QGraphicsView::mousePressEvent(event);

//}

//void GameWindow::mousePressEvent(QGraphicsSceneMouseEvent *e)
//{
//qDebug() << "You clicked ";
//}



