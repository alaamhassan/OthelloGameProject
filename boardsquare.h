#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QPainter>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

class BoardSquare:public QObject,public QGraphicsRectItem
{
    // the Q_OBJECT macro is mandatory for any object that implements signals, slots or properties (from documentation)
    Q_OBJECT
public:
    BoardSquare(int x_coordiante,int y_coordinate,QString SquareName);
  //  QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    //draw disk on the square
    void DrawDisk();

    //setting variables
    void setSquareValidMove(bool isSquareValid);
    void setSquareState(int squareState);

    //initialize the square in case of restart
    void RestartSquareToInitial();

    //set the color of the square
    void setSquareColor();

    int getSquareState();


    //trigger events


   // Reimplement the mouse press event
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    //the coordinate of the sqaure
    int x_coordinate;
    int y_coordinate;

    //width and hight of the square
    int width=60, hight=60;

    //name that uniquly identify the square
    //the x,y of the square wiht respect to the board(36 squares)
    //if the x,y is 1,2 then the name is "12"
    QString SquareName;

    //a varibale that represent the state of the square
    //if 0:empty, 1:black, -1:whtie
    int SqaureState;

    //properities for triggering events
    bool pressed;
    bool isSquareValidMove;


    //the disk image
    QGraphicsPixmapItem *DiskImage;

signals:
    QString sendSignalsToTheGameBoard(QString,QString);

};

#endif // BOARDSQUARE_H
