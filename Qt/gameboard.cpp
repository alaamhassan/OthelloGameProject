#include "gameboard.h"
#include"GameDispalyCalculation.h"


/*Initialize the gameBoard of the board by providing:
 *-----------------------------------------------------------------
 *This functions is used when setting the gameBoard in the gameWindow class
 */
GameBoard::GameBoard()
{

    BoardScene =new QGraphicsScene();

    /*setting the playerTurn to zero, which indicate that player1 will play first.
     * the playerTurn is the index of current player.
     * which is used to access the player in the playerList.
     */
    playerTurn=0;

    /*setting the boardSquareList initialy to empty.
     * which will contains the 64 square of the board.
     * The variable is set in the SetUpBoard() function.
     */
    BoardSqaureList={};

    /*playerList is set initialy to empty.
     * which contains two object of the Player class.
     * The variable is set using the setPlayerList() function, which
     * is called in the constructor of the GameWindow class.
     */
    playerList[0]={};
    playerList[1]={};

    /*setting the 64 square of the board*/
    SetUpBoard();

    /*setting the computerIndexTurn to zero, which indicate that computer1 will play first.
     * the computerIndexTurn is the index of current computerPlayer.
     * which is used to access the player in the computerPlay() function.
     * computerPlay() is used when two computers play together (when choossing-->ComputerVSComputer)
     */
    computerIndexTurn=0;

}

/*---------------------Setter--------------------------*/

/*setting the playerList, which contains two object of the Player class.
 * The variable is set using the setPlayerList() function, which
 * is called in the constructor of the GameWindow class.
 */
void GameBoard::setPlayerList(QObject * GameWindow,QString Player1Name, QString Player2Name)
{
    /*set the player using the player class constructor.
    * which takes three paramters:
    * 1.PlayerName: which is provided from the constructor paramter of the GameWindow class
    * 2.PlayerNumber: indicate the index of the two player, in which the first playing player
    * takes index 0, the other takes 1.
    * 3.IsMaximizer: which is a boolean variable indicate if the current player is maximizer or not.
    * the first player is always black (so it's a maximizer).
    * the second one (is a minimizer).
    * --------------------------------------------------------
    * the two players are connected to the gameWindow class.
    * for the functions in the Player class like (UpdateScore,UpdateRemindedPices...) which is called in
    * the gameBoard class, these functions send a signal to the gameWindow class to update score, reminded Picese..
    * to dispaly them to the user.
    */
    playerList[0]=new Player(Player1Name,0, 1); //Player1 :maximizer
    QObject::connect(playerList[0],SIGNAL(SendPlayerSignal(QStringList)),GameWindow,SLOT(RecievePlayerScoreUpdate(QStringList)));

    playerList[1]=new Player(Player2Name,1, 0); //player2 minimizer
    QObject::connect(playerList[1],SIGNAL(SendPlayerSignal(QStringList)),GameWindow,SLOT(RecievePlayerScoreUpdate(QStringList)));


    //testing
    std::string FirstplayerName=Player1Name.toStdString();

    if(FirstplayerName.compare("Computer1")!=0)InitializeBoardForTesting();

    //end testing

}

/*setting the 64 sqaures in the board.*/
void GameBoard::SetUpBoard()
{
   /*set initialy the top-left corner of the square to be (0,0)
    *this set the first square to be in the top left corner of
    *the QGraphicsScene.
    *for every consequitive square the x,y coordinate will be
    *updated, to draw the whole board.
    */
    int Square_XCoordiante=0;
    int Sqaure_YCoordiante=0;

   /*As the board is 64 squares (8*8), then for every row, 8 squares
    * will be created.
    */
    for(int row=0 ;row<8;row++)
    {
        for(int column=0; column<8; column++)
        {
           /*for every square created, it will be added to the BoardSqaureList, and
            * the QGraphicsScene (BoardScene).
            */
            BoardSquare * square =
                new BoardSquare(Square_XCoordiante,Sqaure_YCoordiante,BoardSquareNumbers[row][column]);

            BoardSqaureList.append(square);

            BoardScene->addItem(square);

           /*connect every square to the function GetResponseFromTheSquare.
            * this connection is done, so that when an event occur in the square (like a mouse pressing event)
            * the square send the board a signal containing both signalMessage, and squareNumber.
            */
            QObject::connect(square,SIGNAL(sendSignalsToTheGameBoard(QString,int)),this,SLOT(GetResponseFromTheSquare(QString,int)));


          /*This check is used to draw the 4 center adjacent squares on the board.
           *1.for square number --> 28( row 3, column 4),35( row 4, column 3) contains black disk(state=1).
           *2.for square number --> 27( row 3, column 3),36( row 4, column 4) contains white disk(state=-1).
           */
           if((row ==3||row==4)&&(column==3||column==4) )
            {
                if((row ==3&&column==4)||(row ==4&&column==3))square->setSquareState(1);

                else square->setSquareState(-1);

                square->DrawDisk();
            }

           /*for every square in the same row, increase the x-coordinate by 60.*/
            Square_XCoordiante+=60;
        }

       /*for every new row the y-coordinate will increase by 60, to start a new row after the previous one.*/
        Sqaure_YCoordiante+=60;

       /*for every new row the x-coordinate will set to zero, to start the new row starting from left.*/
        Square_XCoordiante=0;
    }
}

/*---------------------Getter--------------------------*/

/*get the boardScene*/
QGraphicsScene *GameBoard::GetBoardScene()
{
    return BoardScene;
}



/*---------------------Functions--------------------------*/

/*this function is used in case a computer is playing.
 * the board is disabled to not trigger an event if the player (other
 * than the computer pressed the square).
 */
void GameBoard::DisableBoard()
{
    for(int i=0;i<BoardSqaureList.size();i++)
    {
        BoardSqaureList[i]->setEnabled(false);
    }
}

/*this function to enable the board after a computer play.
 * so that the when player (other than computer) press any square, an event
 * will be triggered.
 */
void GameBoard::EnableBoard()
{
    for(int i=0;i<BoardSqaureList.size();i++)
    {
        BoardSqaureList[i]->setEnabled(true);
    }
}

/*this function is used when two computers play together.
 *note:add comments to the function ##########################################################################################
 */
void GameBoard::computerPlay()
{

    while(!(playerList[playerTurn]->getRemindedPieces()==0&&
             playerList[(playerTurn+1)%2]->getRemindedPieces()==0))

    {
        delay();
        BoardSqaureList[ComputerGame[computerIndexTurn].toInt()]->setSquareValidMove(1);
        BoardSqaureList[ComputerGame[computerIndexTurn].toInt()]->DrawDisk();

        BoardSqaureList[ComputerGame[computerIndexTurn].toInt()]->setSquareState(playerList[playerTurn]->IsPlayerMaximizer());

        playerList[playerTurn]->UpdateRemindedPices();
        playerList[playerTurn]->UpdateScore(calculateScoreForAPlayer(playerList[playerTurn]->IsPlayerMaximizer(),BoardSqaureList));



        playerTurn=(playerTurn+1)%2;
        playerList[playerTurn]->UpdatePlayerTurn();

        computerIndexTurn++;



    }

    if(playerList[playerTurn]->getScore()>playerList[(playerTurn+1)%2]->getScore())
        playerList[playerTurn]->setWinFlag(1);

    else if(playerList[playerTurn]->getScore()<playerList[(playerTurn+1)%2]->getScore())
        playerList[(playerTurn+1)%2]->setWinFlag(1);

    //else if there is a draw
    else
        playerList[playerTurn]->setWinFlag(0);

}

/*this function produces a delay of 1 secound
 *-----------------------------------------------------------------
 * this function is used to delay the computer play for GUI convenience
 *(if this daley wasn't added the game will be so fast, that the user
 * will not be able to observe the game).
 */
void GameBoard::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


/*---------------------EventResponse--------------------------*/

/*This functions takes a signal from the square, when a player press a square
 * a signal containing the signalMessage (squareMessage), and squareNumber (0->63)
 *-------------------------------------------------------------------------------
 * this function is used to generate the board for every turn, then call the Player
 * class functions(which send signals to the GameWindow class, which update the GUI
 * dispalyed to the user).
 * note:add comments to the function #########################################################################################
 */
void GameBoard::GetResponseFromTheSquare(QString SquareMessage,int squareNumber)
{
   /*To be able to use the assignment operator in the if-condition
    * convert the QString to string.
    */
    std::string action = SquareMessage.toStdString();


    QList<std::pair<int,int>> squareValidMoves={std::make_pair(1,2),std::make_pair(1,2)};
    if(action.compare("Switch turns")==0)
    {

        BoardSqaureList[squareNumber]->setSquareState(playerList[playerTurn]->IsPlayerMaximizer());

        playerList[playerTurn]->UpdateRemindedPices();
        playerList[playerTurn]->UpdateScore(calculateScoreForAPlayer(playerList[playerTurn]->IsPlayerMaximizer(),BoardSqaureList));


        //if()
        //forTesting
//        playerList[playerTurn]->UpdateRemindedPices(0);
//        playerList[(playerTurn+1)%2]->UpdateRemindedPices(0);
        //end

        //win,orlost=>check
        //also,check if for two consequitive turns there is no valid moves
        if(playerList[playerTurn]->getRemindedPieces()==0&&
            playerList[(playerTurn+1)%2]->getRemindedPieces()==0)
        {

            //disable the board
            DisableBoard();


            if(playerList[playerTurn]->getScore()>playerList[(playerTurn+1)%2]->getScore())
                playerList[playerTurn]->setWinFlag(1);

            else if(playerList[playerTurn]->getScore()<playerList[(playerTurn+1)%2]->getScore())
                playerList[(playerTurn+1)%2]->setWinFlag(1);

            //else if there is a draw
            else
            playerList[playerTurn]->setWinFlag(0);


       }

        else
        {

        playerTurn=(playerTurn+1)%2;
        playerList[playerTurn]->UpdatePlayerTurn();

        if(!isThereAreValidMoves(squareValidMoves))playerList[playerTurn]->NoValidMovesThisTurn();

        //there a valid move,but player doesn't have enough pieces
        if( playerList[playerTurn]->getRemindedPieces()==0){}


        }



    }

}



//testing
void GameBoard::InitializeBoardForTesting()
{
    for(int i=0;i<BoardSqaureList.size();i++)
    {
        if(i%2==0 &&(!BoardSqaureList[i]->getSquareState()) )
        {
        BoardSqaureList[i]->setSquareValidMove(1);

        }
    }

}

