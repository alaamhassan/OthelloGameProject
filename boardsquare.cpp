#include "boardsquare.h"


BoardSquare::BoardSquare(int x_coordinate,int y_coordinate,QString SquareName)//:QGraphicsRectItem(parent)
{
    //setting the square x,y coordinates
    this->x_coordinate=x_coordinate;
    this->y_coordinate=y_coordinate;

    //setting the name of the sqaure
    this->SquareName=SquareName;

    pressed =false;
    isSquareValidMove=false;

    playerTurn=0;

    setRect(QRectF(x_coordinate,y_coordinate,width,hight));


    //set the image at the same scene of the square
    DiskImage=new QGraphicsPixmapItem();
    DiskImage->setParentItem(this);
}

void BoardSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rec=boundingRect().toRect();
    QBrush brush(Qt::blue);

    if(pressed)
    {
        if(isSquareValidMove)this->DrawDisk();
        else
            brush.setColor(Qt::red);

    }
    else
    {
        if(isSquareValidMove)brush.setColor(Qt::yellow);
        else
            brush.setColor("#006325");
    }

   painter->fillRect(rec,brush);
   painter->drawRect(rec);
}



void BoardSquare::DrawDisk()
{
    QString DiskImagePath;

    if(SqaureState==1)DiskImagePath=":/BoardDisks/OthelloDisks/BlackOthelloDisk-removebg-preview.jpg";//":/BoardDisks/OthelloDisks/BlackOthelloDisk.png";
    else if (SqaureState==-1)DiskImagePath=":/BoardDisks/OthelloDisks/WhiteOthelloDisk-removebg-preview (1).jpg";//":/BoardDisks/OthelloDisks/WhiteOthelloDisk.png";

    DiskImage->setPixmap(DiskImagePath);

    //shiftTheImageToNotOverlabTheSquareBoundary
    DiskImage->setPos(x_coordinate+1,y_coordinate+1);

    DiskImage->show();
}

void BoardSquare::setSquareValidMove()
{
    isSquareValidMove=true;
}

void BoardSquare::setSquareState(int sqaureState)
{
    if(sqaureState==1 ||sqaureState==-1)
    SqaureState=sqaureState;

    else
    {
    //error
    }
}

void BoardSquare::RestartSquareToInitial()
{

}


void BoardSquare::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{



    qDebug()<<"reach the press event";

    //emit sendSignalsToTheGameBoard("Switch turns",playerTurn);

    this->playerTurn= ((playerTurn+1)%2);

    emit sendSignalsToTheGameBoard("Switch turns",playerTurn);

    pressed=true;
    update();

   QGraphicsItem::mousePressEvent(ev);
   //qDebug()<<response[0]<<" "<<response[1];

}

