#include "boardsquare.h"


/*Initialize the square of the board by providing:
 *x_coordinate,y_coordinate: the (x,y) of the top left corner of the square.
 *squareName: the number of the square in the baord (0->63)
 *Also the Disk(white,black) which is set on the square is initialized using the
 *new QGraphicsPixmapItem().
 *-----------------------------------------------------------------
 *This functions is used when setting the board in the gameBoard class
 */
BoardSquare::BoardSquare(int x_coordinate,int y_coordinate,int squareNumber)
{
    /*setting the top left corner of the square (x,y) coordinates*/
    this->x_coordinate=x_coordinate;
    this->y_coordinate=y_coordinate;

    /*setting the number of the square in the baord (0->63)*/
    this->SquareNumber=squareNumber;

    /*The square is initialy not pressed(false), and is set not to be valid move(false).*/
    pressed =false;
    isSquareValidMove=false;

    /*The square state is initialy set to zero (which indicate that square is empty),not
    *1(black disk on the square) or -1(white disk on the square).
    */
    SqaureState=0;

   /*the square is made using the function setRect(),which take the constructor
    *QRectF.
    *QRectF takes the x,y paramaters,width and hight of the rect, which are
    *a constant integers (60*60).
    */
    setRect(QRectF(x_coordinate,y_coordinate,width,hight));

    /*the Disk(white,black) which is set on the square is initialized using the
    *new QGraphicsPixmapItem().
    *set the image at the same scene of the square
    *by passing the (this) keyword the setParentItem().
    */
    DiskImage=new QGraphicsPixmapItem();
    DiskImage->setParentItem(this);

}


/*---------------------Setter--------------------------*/

/*used to set the square to be valid (true) or not(false).*/
void BoardSquare::setSquareValidMove(bool isSquareValid)
{
    isSquareValidMove=isSquareValid;
}

/*used to set the square state*/
void BoardSquare::setSquareState(int sqaureState)
{
    /*if the provided int is 1 or -1:
     * set the square state to provided int.
     * else:
     * no action will be taken.
     */
    if(sqaureState==1 ||sqaureState==-1)
        this->SqaureState=sqaureState;
}


/*---------------------Getter--------------------------*/

/*return the square state*/
int BoardSquare::getSquareState()
{
    return SqaureState;
}


/*---------------------Functions--------------------------*/

/*The function override the paint function in the QGraphicsRectItem class.
 * This function is used to paint the square on the baord by setting it's
 * color, and draw the disk on it according to the value of (pressed,isSquareValidMove,
 * square state).
 * -------------------------------------------------------------------------
 * this function is called using the Update() function, which is called in both the mousePressEvent,
 * and ChangeInvalidSquareColor functions.
 */
void BoardSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rec=boundingRect().toRect();
    QBrush brush("#006325");


    /*The paint function check first if the square is pressed, which is set to true
     * in case of a mousePressEvent using the mousePressEvent function.
     * 1) if the square is pressed, then:
     * the square check further if it the square valid move, which is set int the
     * gameBoard class according to a the valid moves tree generated for the current
     * game state.
     */
    if(pressed)
    {
        /*if the square is a valid move, then:
        *1.1) draw the disk on the square using the DrawDisk() function, and set the
        *square to not be a valid move, as a square which contains a disk can't be
        *a valid move again for the entire game (beacuse if a disk is put on a square,
        *it can't be removed ->according to the game rules).
        */
        if(isSquareValidMove)
        {

            this->DrawDisk();
            this->setSquareValidMove(0);

        }
        /*1.2) else:
        * 1.2.1)check if the square state is zero, which means that the square is empty (dosen't
        * contain any disk), and beacuse the square is not a valid move, then the square will
        * light with the red color(#D92D20) for only 600ms.(to indicate this is not a valid move).
        * 1.2.2)in case if the square state was other than zero (the square contains a disk),
        * then no action will be taken.
        */

        else if(this->getSquareState()==0)
        {
            brush.setColor("#D92D20");

            /*to return the color of the square to green after turning it red after (600) ms
             * the timer and the ChangeInvalidSquareColor were connected using QTimer::singleShot
             * which make only a single call (better in performance than using usual connect, to
             * not make a continous connection between the two functions when it's not needed)
             * to the function ChangeInvalidSquareColor, when 600ms passes after turning the square
             * to red.
             * when ChangeInvalidSquareColor is called the paint function is called using the Update()
             * function, this time the point (2.3) will be accessed.
             */
            QTimer::singleShot(600, this, &BoardSquare::ChangeInvalidSquareColor);

        }

    }
     /* 2) else:
     * if the mouse is not pressed (this check is used in three cases, which the square is not pressed
     * by the user):
     */
    else
    {
        /*2.1)when initializing the board (to draw the 4 adjacent squares in the center of the board).
        * 2.2)when the computer is playing (draw the disk on the square choosen by the computer)
        */
        if(isSquareValidMove)this->DrawDisk();

        /*2.3)when the user press an invalid square (point 1.2.1), after a 600ms the function
        *ChangeInvalidSquareColor() will be called, which update the square(call the paint function),
        *and the square color will return to green.
        */
        else if(this->getSquareState()==0)
            brush.setColor("#006325");
    }


   painter->fillRect(rec,brush);
   painter->drawRect(rec);

}


/*this is the function used to draw the disk on the square.*/
void BoardSquare::DrawDisk()
{
    QString DiskImagePath="";

   /*according to the square state, the disk image will be choosen:
    * 1)if 1: then choose a dark disk image.
    * 2)if -1: choose a white disk image.
    * 3)else: this means that the square is empty, and a valid move. In this
    * case a circule image will be choosen.
    */
    if(SqaureState==1)DiskImagePath=":/BoardDisks/OthelloDisks/DarkDisk.jpg";
    else if (SqaureState==-1)DiskImagePath=":/BoardDisks/OthelloDisks/WhiteDisk.jpg";
    else if (isSquareValidMove)DiskImagePath=":/BoardDisks/OthelloDisks/validDisk2.jpg";

    DiskImage->setPixmap(DiskImagePath);

    /*shift the disk image to not overlab the square boundary.*/
    DiskImage->setPos(x_coordinate+1,y_coordinate+1);

    /*show the image*/
    DiskImage->show();
}

void BoardSquare::hideDisk()
{
    DiskImage->hide();
}


/*---------------------Events--------------------------*/

/*this function is accessed when the user press the square.*/
void BoardSquare::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
   /*check if the square is valid move.
    *if it's, then a signal will be sent the game board to indicate that
    *the player has choosen a square and to switch the turns for the next
    *player.
    *the squareNumber is also send to update the BoardSqaureList (which contains
    *a list of the 64 squares of the board) in the gameBoard class.
    */
    if(isSquareValidMove)
    {
        emit sendSignalsToTheGameBoard("Switch turns",this->SquareNumber);
    }

   /*the pressed variable is set to true, and the update() function will be
    * called to execuate the paint function and update the square accordingly.
    */
    pressed=true;
    update();

    QGraphicsItem::mousePressEvent(ev);

}

/*this function is used to change the invalid square from red
 * to green after 600ms, as it connected with the QTimer in
 * the paint function using the line:
 * QTimer::singleShot(600, this, &BoardSquare::ChangeInvalidSquareColor);
 */
void BoardSquare::ChangeInvalidSquareColor()
{
    /*the pressed variable is set to false, and the update() function will be
    * called to execuate the paint function and update the square accordingly.
    */
    pressed=false;
    update();
}


