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

    setRect(QRectF(x_coordinate,y_coordinate,width,hight));
    //set the image at the same scene of the square
    DiskImage=new QGraphicsPixmapItem();
    DiskImage->setParentItem(this);

//    setFlag(ItemIsMovable);
//    this ->setFlags(QGraphicsItem::ItemIsFocusable);
//    this->setFocus();
//    this->setFlags(QGraphicsItem::ItemIsSelectable);
//    this ->setAcceptHoverEvents(true);
    //this ->setAcceptedMouseButtons(Qt::LeftButton);
}

//QRectF BoardSquare::boundingRect() const
//{
//    return QRectF(x_coordinate,y_coordinate,width,hight);


//}

void BoardSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec=boundingRect().toRect();
    QBrush brush(Qt::blue);

    if(pressed)
    {
        brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::green);
    }

   painter->fillRect(rec,brush);
   painter->drawRect(rec);
}



void BoardSquare::DrawDisk()
{
    QString DiskImagePath;

    if(SqaureState==1)DiskImagePath=":/BoardDisks/OthelloDisks/BlackOthelloDisk.png";
    else if (SqaureState==-1)DiskImagePath=":/BoardDisks/OthelloDisks/WhiteOthelloDisk.png";

    DiskImage->setPixmap(DiskImagePath);
    DiskImage->setPos(x_coordinate,y_coordinate);
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

// When clicked, space name is sent to Display's slot
void BoardSquare::mousePressEvent(QGraphicsSceneMouseEvent *ev){
    if(ev->buttons() == Qt::LeftButton){
    qDebug() << "You clicked " << SquareName;
    }
            pressed=true;
            update();
            QGraphicsItem::mousePressEvent(ev);
}


//    emit sendSignalsToTheBoard({"draw disk",SquareName});

//void BoardSquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{

//           pressed=true;
//           update();


//   qDebug()<<"reach the press event";
//   if(isSquareValidMove)
//   {
//        //        response[0]="draw disk";
//        //        response[1]=SquareName;

//        emit sendSignalsToTheBoard({"draw disk",SquareName});
//   }

//   else
//   {
//        //        response[0]="light the square with red";
//        //        response[1]=SquareName;

//        emit sendSignalsToTheBoard({"light the square with red",SquareName});
//   }

//   QGraphicsItem::mousePressEvent(event);
//   //qDebug()<<response[0]<<" "<<response[1];

//}
// emit sendSignalsToTheBoard("SqureIsPressed");

//        pressed=true;
//        update();
//        QGraphicsItem::mousePressEvent(event);


//void BoardSquare::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    //QStringList response;

//    qDebug()<<"reach the realse event";
//    if(isSquareValidMove)
//    {
////        response[0]="draw disk";
////        response[1]=SquareName;

//        emit sendSignalsToTheBoard({"draw disk",SquareName});
//    }

//    else
//    {
////        response[0]="light the square with red";
////        response[1]=SquareName;

//        emit sendSignalsToTheBoard({"light the square with red",SquareName});
//    }

//    //qDebug()<<response[0]<<" "<<response[1];

//}

//    pressed=false;
//    update();
//    QGraphicsItem::mousePressEvent(event);
