#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "qgraphicsscene.h"
//#include "boardsquare.h"
#include "gameboard.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include<QDebug>
//#include <QMouseEvent>
//#include <QGraphicsView>
namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
//    void mouseMoveEvent(QMouseEvent *event);
   // void mousePressEvent(QGraphicsSceneMouseEvent *e) ;

//protected:
//    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::GameWindow *ui;
    QGraphicsScene* GameScene;
    QGraphicsRectItem* GameBoardRectangle;
    BoardSquare *boardSquare;

    GameBoard* gameBoard;
};

#endif // GAMEWINDOW_H
