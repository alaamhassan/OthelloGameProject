#include "boardsquare.h"
#include"QTimer"

BoardSquare::BoardSquare(int x_coordinate,int y_coordinate,QString SquareName)//:QGraphicsRectItem(parent)
{
    //setting the square x,y coordinates
    this->x_coordinate=x_coordinate;
    this->y_coordinate=y_coordinate;

    //setting the name of the sqaure
    this->SquareName=SquareName;

    pressed =false;
    isSquareValidMove=false;

    //playerTurn=0;


    SqaureState=0;

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
    QBrush brush("#006325");

    bool ChangeColorFlag=0;

    if(pressed)
    {
        if(isSquareValidMove)
        {

            this->DrawDisk();
            this->setSquareValidMove(0);

        }
        else if(this->getSquareState()==0)
        {
            brush.setColor("#D92D20");//Qt::red



            // Create a timer and set its interval to 3 seconds
            QTimer timer;
            timer.setInterval(500);

            // Connect the timer's timeout signal to a slot that changes the color back
            connect(&timer, &QTimer::timeout, [&brush]() {
                brush.setColor("#006325"); // or any other color you want
            });

            // Start the timer
            timer.start();

            ChangeColorFlag=1;

        }

    }
    else
    {
        if(isSquareValidMove)this->DrawDisk();//brush.setColor("#F79009");//Qt::yellow
        else if(this->getSquareState()==0)
            brush.setColor("#006325");
    }

   painter->fillRect(rec,brush);
   painter->drawRect(rec);

   if(ChangeColorFlag) ChangeInvalidSquareColor(painter);
}



void BoardSquare::DrawDisk()
{
    QString DiskImagePath;

   if(SqaureState==1)DiskImagePath=":/BoardDisks/OthelloDisks/DarkDisk.jpg";
   else if (SqaureState==-1)DiskImagePath=":/BoardDisks/OthelloDisks/WhiteDisk.jpg";
   else DiskImagePath=":/BoardDisks/OthelloDisks/validDisk2.jpg";

    DiskImage->setPixmap(DiskImagePath);

    //shiftTheImageToNotOverlabTheSquareBoundary
    DiskImage->setPos(x_coordinate+1,y_coordinate+1);

    DiskImage->show();
}

void BoardSquare::hideDisk()
{
    DiskImage->hide();
}

void BoardSquare::setSquareValidMove(bool isSquareValid)
{
    isSquareValidMove=isSquareValid;
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

int BoardSquare::getSquareState()
{
    return SqaureState;
}


void BoardSquare::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{



    qDebug()<<"reach the press event";

    if(isSquareValidMove)
    {


    emit sendSignalsToTheGameBoard("Switch turns",this->SquareName);
    }

    pressed=true;
    update();

   QGraphicsItem::mousePressEvent(ev);


}

void BoardSquare::ChangeInvalidSquareColor(QPainter *painter)
{
   QRectF rec=boundingRect().toRect();
   QBrush brush("#006325");

   painter->fillRect(rec,brush);
   painter->drawRect(rec);

}


