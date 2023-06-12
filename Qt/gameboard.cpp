#include "gameboard.h"
#include"cmath"


/*Initialize the gameBoard
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

    possiblePositions={};

}

/*---------------------Setter--------------------------*/

/*setting the playerList, which contains two object of the Player class.
 * The variable is set using the setPlayerList() function, which
 * is called in the constructor of the GameWindow class.
 * -->the GameWindow where passed to be able to establish a connection between the two palyers
 * and the gameWindow class.
 */
void GameBoard::setPlayerList(QObject * GameWindow,QString Player1Name, QString Player2Name, int PlayerLevels[])
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


    playerList[0]=new Player(Player1Name,0, 1,PlayerLevels[0]); //Player1 :maximizer
    QObject::connect(playerList[0],SIGNAL(SendPlayerSignal(QStringList)),GameWindow,SLOT(ReciveResponseFromThePlayer(QStringList)));


    playerList[1]=new Player(Player2Name,1, 0,PlayerLevels[1]); //player2 minimizer
    QObject::connect(playerList[1],SIGNAL(SendPlayerSignal(QStringList)),GameWindow,SLOT(ReciveResponseFromThePlayer(QStringList)));


    //testing
    std::string FirstplayerName=Player1Name.toStdString();

    if(FirstplayerName.compare("Computer1")!=0)
    {
        possiblePositions=getPossiblePositions(playerList[playerTurn]->IsPlayerMaximizer());
        playerList[playerTurn]->setIsThereValidMoves(possiblePositions.size()?1:0);
    }


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

            BoardSqaureList.push_back(square);

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

       /*for every new row the x-coordinate will be set to zero, to start the new row starting from left.*/
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

    std::string PlayerName=playerList[playerTurn]->getPlayerName().toStdString();

    while((PlayerName.compare("Player")!=0)&&(!(playerList[playerTurn]->getRemindedPieces()==0&&
             playerList[(playerTurn+1)%2]->getRemindedPieces()==0)||
            (playerList[playerTurn]->IsThereValidMoves()==0&&playerList[(playerTurn+1)%2]->IsThereValidMoves()==0)))


    {

//        if(PlayerName.compare("Computer")!=0)
//        {
//        possiblePositions=getPossiblePositions(playerList[(playerTurn+1)%2]->IsPlayerMaximizer());
//        playerList[(playerTurn+1)%2]->setIsThereValidMoves(possiblePositions.size()?1:0);
//        }

       // restartValidMovesToZero(possiblePositions);
        delay();

        std::pair<int, int> index =getBestPlay(playerList[playerTurn]->IsPlayerMaximizer(),playerList[playerTurn]->getPlayerLevel());


        qDebug()<<"Positions_size:"<<possiblePositions.size();

        if(PlayerName.compare("Computer")!=0)
        {
        playerList[playerTurn]->setIsThereValidMoves(possiblePositions.size());
        }

        if(playerList[playerTurn]->IsThereValidMoves()&&(!(playerList[playerTurn]->getRemindedPieces()==0)))
            {

            qDebug()<<"playerLevel"<<playerList[playerTurn]->getPlayerLevel();


            BoardSqaureList[(BoardSquareNames[index.first][index.second]).toInt()]->setSquareState(playerList[playerTurn]->IsPlayerMaximizer());


            update_array(index.first, index.second , playerList[playerTurn]->IsPlayerMaximizer());

            playerList[playerTurn]->UpdateRemindedPices();

            playerList[playerTurn]->UpdateScore(calculateScoreForAPlayer(playerList[playerTurn]->IsPlayerMaximizer(),BoardSqaureList));
            playerList[(playerTurn+1)%2]->UpdateScore(calculateScoreForAPlayer(playerList[(playerTurn+1)%2]->IsPlayerMaximizer(),BoardSqaureList));

            if(PlayerName.compare("Computer")!=0){

            possiblePositions=getPossiblePositions(playerList[(playerTurn+1)%2]->IsPlayerMaximizer());
            playerList[(playerTurn+1)%2]->setIsThereValidMoves(possiblePositions.size()?1:0);
            restartValidMovesToZero(possiblePositions);
            }

            playerTurn=(playerTurn+1)%2;

            playerList[playerTurn]->UpdatePlayerTurn();
          }

            else if((PlayerName.compare("Player")!=0)&&(!(playerList[playerTurn]->getRemindedPieces()==0&&
                         playerList[(playerTurn+1)%2]->getRemindedPieces()==0)||
                        (playerList[playerTurn]->IsThereValidMoves()==0&&playerList[(playerTurn+1)%2]->IsThereValidMoves()==0)))

            {
            if((!(playerList[playerTurn]->IsThereValidMoves())&&(playerList[(playerTurn+1)%2]->IsThereValidMoves()))
                       ||((playerList[playerTurn]->getRemindedPieces()==0)&&(playerList[playerTurn]->IsThereValidMoves())))
                      {

                       qDebug()<<"player1RemindedPices"<<playerList[playerTurn]->getRemindedPieces();
                        qDebug()<<"Player2RemindedPices"<<playerList[(playerTurn+1)%2]->getRemindedPieces();


                        qDebug()<<"player1validMoves"<<playerList[playerTurn]->IsThereValidMoves();
                        qDebug()<<"Player2validMoves"<<playerList[(playerTurn+1)%2]->IsThereValidMoves();

                        if(playerList[playerTurn]->getRemindedPieces()==1)
                        {
                            int a=1;
                        }

                        restartValidMovesToZero(possiblePositions);
                        playerTurn=(playerTurn+1)%2;


                        playerList[playerTurn]->UpdatePlayerTurn();

                        playerList[playerTurn]->NoValidMovesThisTurn();
                      }


            }


         PlayerName=playerList[playerTurn]->getPlayerName().toStdString();

    }


    if(((playerList[playerTurn]->getRemindedPieces()==0&&
           playerList[(playerTurn+1)%2]->getRemindedPieces()==0)||
         (playerList[playerTurn]->IsThereValidMoves()==0&&playerList[(playerTurn+1)%2]->IsThereValidMoves()==0)))

    {
        if(playerList[playerTurn]->getScore()>playerList[(playerTurn+1)%2]->getScore())
            playerList[playerTurn]->setWinFlag(1);

        else if(playerList[playerTurn]->getScore()<playerList[(playerTurn+1)%2]->getScore())
            playerList[(playerTurn+1)%2]->setWinFlag(1);

        //else if there is a draw
        else
            playerList[playerTurn]->setWinFlag(0);
    }


    if(PlayerName.compare("Player")==0)
    {
        EnableBoard();
       // restartValidMovesToZero(possiblePositions);
    }

}

/*this function produces a delay of 1 secound
 *-----------------------------------------------------------------
 * this function is used to delay the computer play for GUI convenience
 *(if this daley wasn't added the game will be so fast, that the user
 * will not be able to observe the game).
 */
void GameBoard::delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(1000);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


/*---------------------EventResponse--------------------------*/

/*This functions takes a signal from the square, when a player press a square
 * a signal containing the signalMessage (squareMessage), and squareNumber (0->63) is
 * sent to this function.
 *-------------------------------------------------------------------------------
 * this function is used to generate the current board for every turn, then call the Player
 * class functions(which send signals to the GameWindow class, which update the GUI
 * dispalyed to the user).
 * note:add comments to the function #########################################################################################
 */
void GameBoard::GetResponseFromTheSquare(QString SquareMessage,int squareNumber)
{
    std::string PlayerName=playerList[playerTurn]->getPlayerName().toStdString();

    /*To be able to use the assignment operator in the if-condition
    * convert the QString to string.
    */
    std::string action = SquareMessage.toStdString();


    int SquareRow;
    int SquareColumn;

    if(action.compare("Switch turns")==0)
    {

        BoardSqaureList[squareNumber]->setSquareState(playerList[playerTurn]->IsPlayerMaximizer());

        restartValidMovesToZero(possiblePositions);

        SquareRow=std::ceil(squareNumber/8);
        SquareColumn=squareNumber-(SquareRow*8);
        update_array(SquareRow, SquareColumn , playerList[playerTurn]->IsPlayerMaximizer());

        playerList[playerTurn]->UpdateRemindedPices();
        playerList[playerTurn]->UpdateScore(calculateScoreForAPlayer(playerList[playerTurn]->IsPlayerMaximizer(),BoardSqaureList));
        playerList[(playerTurn+1)%2]->UpdateScore(calculateScoreForAPlayer(playerList[(playerTurn+1)%2]->IsPlayerMaximizer(),BoardSqaureList));


        //validMoves

        possiblePositions=getPossiblePositions(playerList[(playerTurn+1)%2]->IsPlayerMaximizer());
        playerList[(playerTurn+1)%2]->setIsThereValidMoves(possiblePositions.size()?1:0);


        //win,orlost=>check
        //also,check if for two consequitive turns there is no valid moves
        if((playerList[playerTurn]->getRemindedPieces()==0&&
            playerList[(playerTurn+1)%2]->getRemindedPieces()==0)||
            (playerList[playerTurn]->IsThereValidMoves()==0&&playerList[(playerTurn+1)%2]->IsThereValidMoves()==0))
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

            if(PlayerName.compare("Computer")!=0){

                if((!playerList[playerTurn]->IsThereValidMoves())||(playerList[playerTurn]->getRemindedPieces()==0))
                {
                    playerList[playerTurn]->NoValidMovesThisTurn();

                    playerTurn=(playerTurn+1)%2;
                    playerList[playerTurn]->UpdatePlayerTurn();

                    restartValidMovesToZero(possiblePositions);

                    possiblePositions=getPossiblePositions(playerList[playerTurn]->IsPlayerMaximizer());
                   playerList[playerTurn]->setIsThereValidMoves(possiblePositions.size()?1:0);

                }
            }
       }

       PlayerName=playerList[playerTurn]->getPlayerName().toStdString();

       if(PlayerName.compare("Computer")==0)
       {
        DisableBoard();
        restartValidMovesToZero(possiblePositions);
        computerPlay();

       }
    }
}


//void GameBoard::computerPlay()
//{

//    std::string PlayerName=playerList[playerTurn]->getPlayerName().toStdString();

//    /*To be able to use the assignment operator in the if-condition
//    * convert the QString to string.
//    */

//    int SquareRow;
//    int SquareColumn;


//    while((PlayerName.compare("Player")!=0)&&(!(playerList[playerTurn]->getRemindedPieces()==0&&
//                                                     playerList[(playerTurn+1)%2]->getRemindedPieces()==0)||
//                                                   (playerList[playerTurn]->IsThereValidMoves()==0&&playerList[(playerTurn+1)%2]->IsThereValidMoves()==0)))
//       restartValidMovesToZero(possiblePositions);

//       SquareRow=std::ceil(squareNumber/8);
//       SquareColumn=squareNumber-(SquareRow*8);
//       update_array(SquareRow, SquareColumn , playerList[playerTurn]->IsPlayerMaximizer());

//       playerList[playerTurn]->UpdateRemindedPices();
//       playerList[playerTurn]->UpdateScore(calculateScoreForAPlayer(playerList[playerTurn]->IsPlayerMaximizer(),BoardSqaureList));
//       playerList[(playerTurn+1)%2]->UpdateScore(calculateScoreForAPlayer(playerList[(playerTurn+1)%2]->IsPlayerMaximizer(),BoardSqaureList));


//       //validMoves

//       possiblePositions=getPossiblePositions(playerList[(playerTurn+1)%2]->IsPlayerMaximizer());
//       playerList[(playerTurn+1)%2]->setIsThereValidMoves(possiblePositions.size()?1:0);


//       //win,orlost=>check
//       //also,check if for two consequitive turns there is no valid moves
//       if((playerList[playerTurn]->getRemindedPieces()==0&&
//            playerList[(playerTurn+1)%2]->getRemindedPieces()==0)||
//           (playerList[playerTurn]->IsThereValidMoves()==0&&playerList[(playerTurn+1)%2]->IsThereValidMoves()==0))
//       {

//        //disable the board
//        DisableBoard();


//        if(playerList[playerTurn]->getScore()>playerList[(playerTurn+1)%2]->getScore())
//                playerList[playerTurn]->setWinFlag(1);

//        else if(playerList[playerTurn]->getScore()<playerList[(playerTurn+1)%2]->getScore())
//                playerList[(playerTurn+1)%2]->setWinFlag(1);

//        //else if there is a draw
//        else
//                playerList[playerTurn]->setWinFlag(0);


//       }

//       else
//       {

//        playerTurn=(playerTurn+1)%2;
//        playerList[playerTurn]->UpdatePlayerTurn();

//        if(PlayerName.compare("Computer")!=0){

//                if((!playerList[playerTurn]->IsThereValidMoves())||(playerList[playerTurn]->getRemindedPieces()==0))
//                {
//                   playerList[playerTurn]->NoValidMovesThisTurn();

//                   playerTurn=(playerTurn+1)%2;
//                   playerList[playerTurn]->UpdatePlayerTurn();

//                   restartValidMovesToZero(possiblePositions);

//                   possiblePositions=getPossiblePositions(playerList[playerTurn]->IsPlayerMaximizer());
//                   playerList[playerTurn]->setIsThereValidMoves(possiblePositions.size()?1:0);

//                }
//        }
//       }

//       PlayerName=playerList[playerTurn]->getPlayerName().toStdString();

//       if(PlayerName.compare("Computer")==0)
//       {
//        DisableBoard();
//        restartValidMovesToZero(possiblePositions);
//        computerPlay();

//       }
//    }


//}
//    //void GameBoard::GetResponseFromTheSquare(QString SquareMessage,int squareNumber)
//    //{



//    //    /*To be able to use the assignment operator in the if-condition
//    //    * convert the QString to string.
//    //    */
//    //    std::string action = SquareMessage.toStdString();


//    //    int SquareRow;
//    //    int SquareColumn;
//    //    int skipTurn=0;

//    //    int validMovesPlayer=0;

//    //    if(action.compare("Switch turns")==0)
//    //    {
//    //        BoardSqaureList[squareNumber]->setSquareState(playerList[playerTurn]->IsPlayerMaximizer());



//    //        restartValidMovesToZero(possiblePositions);

//    //        //validMoves

//    //      //  do
//    //       // {
//    //           // if(!skipTurn)
//    //                validMovesPlayer=(playerTurn+1)%2;
//    ////            else
//    ////                validMovesPlayer=playerTurn;

//    //            possiblePositions=getPossiblePositions(playerList[validMovesPlayer]->IsPlayerMaximizer());

//    //            playerList[validMovesPlayer]->setIsThereValidMoves(possiblePositions.size()?1:0);

//    //            qDebug()<<"Positions_size:"<<possiblePositions.size();


//    //            if(playerList[playerTurn]->getScore()+playerList[(playerTurn+1)%2]->getScore()==62)

//    //            {
//    //                int a=1;

//    //            }


//    //            //win,orlost=>check
//    //            //also,check if for two consequitive turns there is no valid moves
//    //      //      if((playerList[playerTurn]->getRemindedPieces()==0&&
//    ////                 playerList[(playerTurn+1)%2]->getRemindedPieces()==0)||
//    ////                (playerList[playerTurn]->IsThereValidMoves()==0&&playerList[(playerTurn+1)%2]->IsThereValidMoves()==0)||
//    ////                (playerList[playerTurn]->getScore()+playerList[(playerTurn+1)%2]->getScore()==64))
//    ////            {

//    ////                //disable the board
//    ////                DisableBoard();


//    ////                if(playerList[playerTurn]->getScore()>playerList[(playerTurn+1)%2]->getScore())
//    ////                    playerList[playerTurn]->setWinFlag(1);

//    ////                else if(playerList[playerTurn]->getScore()<playerList[(playerTurn+1)%2]->getScore())
//    ////                    playerList[(playerTurn+1)%2]->setWinFlag(1);

//    ////                //else if there is a draw
//    ////                else
//    ////                    playerList[playerTurn]->setWinFlag(0);


//    ////                skipTurn=0;

//    ////            }

//    ////            else
//    //          // {
//    //                //if((playerList[validMovesPlayer]->IsThereValidMoves()))
//    //              //  {

//    ////                    if(playerList[playerTurn]->getRemindedPieces()==0)
//    ////                    {
//    ////                        playerList[playerTurn]->TakePiecesFromOppenent();
//    ////                        playerList[(playerTurn+1)%2]->UpdateRemindedPices();
//    ////                        playerList[playerTurn]->UpdateRemindedPices(1);

//    ////                    }



//    //                    SquareRow=std::ceil(squareNumber/8);
//    //                    SquareColumn=squareNumber-(SquareRow*8);
//    //                    update_array(SquareRow, SquareColumn , playerList[playerTurn]->IsPlayerMaximizer());


//    //                    playerList[playerTurn]->UpdateRemindedPices();
//    //                    playerList[playerTurn]->UpdateScore(calculateScoreForAPlayer(playerList[playerTurn]->IsPlayerMaximizer(),BoardSqaureList));
//    //                    playerList[(playerTurn+1)%2]->UpdateScore(calculateScoreForAPlayer(playerList[(playerTurn+1)%2]->IsPlayerMaximizer(),BoardSqaureList));

//    //                    skipTurn=0;

//    //                    if(!((playerList[playerTurn]->getRemindedPieces()==0&&
//    //                         playerList[(playerTurn+1)%2]->getRemindedPieces()==0)||
//    //                        (playerList[playerTurn]->IsThereValidMoves()==0&&playerList[(playerTurn+1)%2]->IsThereValidMoves()==0)||
//    //                          (playerList[playerTurn]->getScore()+playerList[(playerTurn+1)%2]->getScore()==64)))
//    //                    {
//    //                        if((!playerList[validMovesPlayer]->IsThereValidMoves())||(playerList[validMovesPlayer]->getRemindedPieces()==0))
//    //                        {
//    //                            playerTurn=(playerTurn+1)%2;

//    //                            playerList[playerTurn]->UpdatePlayerTurn();

//    //                            playerList[playerTurn]->NoValidMovesThisTurn();

//    //                            skipTurn=1;


//    //                        }

//    //                            this->playerTurn=(playerTurn+1)%2;

//    //                             playerList[playerTurn]->UpdatePlayerTurn();

//    //                            if(skipTurn)
//    //                             {

//    ////                            restartValidMovesToZero(possiblePositions);

//    ////                            possiblePositions=getPossiblePositions(playerList[playerTurn]->IsPlayerMaximizer());

//    ////                            playerList[playerTurn]->setIsThereValidMoves(possiblePositions.size()?1:0);
//    ////                            skipTurn=0;

//    ////                            }
//    //                    }

//    //                    else

//    //                    {
//    //                            //disable the board
//    //                            DisableBoard();


//    //                            if(playerList[playerTurn]->getScore()>playerList[(playerTurn+1)%2]->getScore())
//    //                            playerList[playerTurn]->setWinFlag(1);

//    //                            else if(playerList[playerTurn]->getScore()<playerList[(playerTurn+1)%2]->getScore())
//    //                            playerList[(playerTurn+1)%2]->setWinFlag(1);

//    //                            //else if there is a draw
//    //                            else
//    //                            playerList[playerTurn]->setWinFlag(0);


//    //                            skipTurn=0;

//    //                    }


//    ////   }

//    //      //  }while(skipTurn);
//    //    }


//    //}



//testing

void GameBoard::InitializeBoardForTesting()
{
    for(int i=0;i<BoardSqaureList.size();i++)
    {

        BoardSqaureList[i]->setSquareValidMove(1);
    }

    BoardSqaureList[0]->setSquareValidMove(1);
}

void GameBoard::restartValidMovesToZero(std::vector<std::pair<int, int>> possiblePositions)
{
    int index;
    for(int i=0;i<possiblePositions.size();i++)
    {
        index=(BoardSquareNames[possiblePositions[i].first][possiblePositions[i].second]).toInt();

        if(BoardSqaureList[index]->getSquareState()==0)
        {
        BoardSqaureList[index]->setSquareValidMove(0);
        BoardSqaureList[index]->hideDisk();
        }
    }

}

/*----------------------------------functions---------------------------------*/

/*---------------------------------UpdateBoard--------------------------*/
void GameBoard::update_array(int i_org, int j_org, int player) {
   int i = i_org;
    int j = j_org;
    bool flag = 0;

    //updating rows above

    while ((i != 0) &&(BoardSqaureList[(BoardSquareNames[i - 1][j]).toInt()]->getSquareState()!= 0)) {

        i--;

        if (BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState() == player) {
        i++;
        while (i != i_org) {
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->setSquareState(player);
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->DrawDisk();
            i++;
        }
        flag = 1;
        }
        if (flag == 1) break;
    }

    //updating rows below
    i = i_org;     j = j_org;     flag = 0;

    while (i != 8 && (BoardSqaureList[(BoardSquareNames[i + 1][j]).toInt()]->getSquareState() != 0)) {
        i++;

        if (BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState() == player) {
        i--;
        while (i != i_org) {
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->setSquareState(player);
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->DrawDisk();
            i--;
        }
        flag = 1;
        }
        if (flag == 1) break;

    }

    //updating coloums to the left
    i = i_org;     j = j_org;     flag = 0;


    while (j != 0 && (BoardSqaureList[(BoardSquareNames[i][j-1]).toInt()]->getSquareState() != 0)) {
        j--;

        if (BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState() == player) {
        j++;
        while (j != j_org) {
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->setSquareState(player);
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->DrawDisk();
            j++;
        }
        flag = 1;
        }
        if (flag == 1) break;
    }


    //updating coloums to the right
    i = i_org;     j = j_org;     flag = 0;
    while (j != 8 && (BoardSqaureList[(BoardSquareNames[i][j+1]).toInt()]->getSquareState() != 0)) {
        j++;

        if (BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState() == player) {
        j--;
        while (j != j_org) {
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->setSquareState(player);
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->DrawDisk();
            j--;
        }
        flag = 1;
        }
        if (flag == 1) break;
    }


    //updating up_left diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i != 0 && j!= 0 && (BoardSqaureList[(BoardSquareNames[i-1][j-1]).toInt()]->getSquareState() != 0)) {
        i--; j--;

        if (BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState() == player) {
        i++; j++;
        while (i != i_org) {
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->setSquareState(player);
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->DrawDisk();
            i++; j++;
        }
        flag = 1;
        }
        if (flag == 1) break;
    }

    //updating down-right diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i!= 8 && j != 8 && (BoardSqaureList[(BoardSquareNames[i+1][j + 1]).toInt()]->getSquareState() != 0)) {
        i++;  j++;

        if (BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState() == player) {
        i--;  j--;
        while (j != j_org) {
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->setSquareState(player);
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->DrawDisk();
            i--;  j--;
        }
        flag = 1;
        }
        if (flag == 1) break;
    }

    //updating up-right diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i != 0 && j != 8 && (BoardSqaureList[(BoardSquareNames[i - 1][j + 1]).toInt()]->getSquareState() != 0)) {
        i--;  j++;

        if (BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState() == player) {
        i++;  j--;
        while (j != j_org) {
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->setSquareState(player);
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->DrawDisk();
            i++;  j--;
        }
        flag = 1;
        }
        if (flag == 1) break;
    }

    //updating down-left diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i != 8 && j != 0 && (BoardSqaureList[(BoardSquareNames[i + 1][j - 1]).toInt()]->getSquareState() != 0)) {
        i++;  j--;

        if (BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState() == player) {
        i--;  j++;
        while (j != j_org) {
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->setSquareState(player);
            BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->DrawDisk();
            i--;  j++;
        }
        flag = 1;
        }
        if (flag == 1) break;
    }

}


/*---------------------------------GenerateValidMoves--------------------------*/
// Function to check if a move is valid
bool GameBoard::isValidMove(int row, int col, int player) {


    // Check if the position is within the board limits
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }



    // Check if the position is empty
    if (BoardSqaureList[(BoardSquareNames[row][col]).toInt()]->getSquareState() != 0) {
        return false;
    }

    // Check if the position is a valid move in any direction
    for (int dirX = -1; dirX <= 1; dirX++) {
        for (int dirY = -1; dirY <= 1; dirY++) {
        // Skip the current position and diagonals
        if (dirX == 0 && dirY == 0) {
            continue;
        }

        int currX = row + dirX;
        int currY = col + dirY;

        // Check if there is an opponent piece adjacent in the current direction
        if (currX >= 0 && currX < BOARD_SIZE && currY >= 0 && currY < BOARD_SIZE &&
            BoardSqaureList[(BoardSquareNames[currX][currY]).toInt()]->getSquareState() != player
            && BoardSqaureList[(BoardSquareNames[currX][currY]).toInt()]->getSquareState() != 0) {

            // Continue moving in the current direction until reaching a player's piece or an empty position
            while (currX >= 0 && currX < BOARD_SIZE && currY >= 0 &&
                   currY < BOARD_SIZE && BoardSqaureList[BoardSquareNumbers[currX][currY]]->getSquareState() != player &&
                   BoardSqaureList[(BoardSquareNames[currX][currY]).toInt()]->getSquareState() != 0) {

                currX += dirX;
                currY += dirY;
            }

            // If a player's piece is found, the move is valid
            if (currX >= 0 && currX < BOARD_SIZE && currY >= 0 &&
                currY < BOARD_SIZE && BoardSqaureList[(BoardSquareNames[currX][currY]).toInt()]->getSquareState() == player) {

                return true;
            }
        }
        }
    }

    // No valid move found in any direction
    return false;
}



// Function to return all possible positions to play in Othello
std::vector<std::pair<int, int>> GameBoard::getPossiblePositions(int player) {

    std::vector<std::pair<int, int>> possiblePositions;

    // Loop through the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
        // Check if the current position is empty
        if (BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState() == 0) {
            // Check if the current position is a valid move for the player
            if (isValidMove(i, j, player)) {
                possiblePositions.push_back(std::make_pair(i, j));

                BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->setSquareValidMove(1);
                BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->DrawDisk();
            }
        }
        }
    }

    return possiblePositions;
}

/*---------------------------------MinMaxAlgo--------------------------*/
void GameBoard::copyOriginalBoard(int newBoard[BOARD_SIZE][BOARD_SIZE])
{
    int i,j;
    for(i=0;i<BOARD_SIZE;i++)
    {
        for(j=0;j<BOARD_SIZE;j++)
        {
        newBoard[i][j]=BoardSqaureList[(BoardSquareNames[i][j]).toInt()]->getSquareState();
        }

    }
}

void GameBoard::copyBoard(int board[BOARD_SIZE][BOARD_SIZE],int newBoard[BOARD_SIZE][BOARD_SIZE])
{
    int i,j;
    for(i=0;i<BOARD_SIZE;i++)
    {
        for(j=0;j<BOARD_SIZE;j++)
        {
        newBoard[i][j]=board[i][j];
        }

    }
}

std::pair<int, int> GameBoard::getBestPlay(int player, int depth) {
    int bestPlayScore = (player==BLACK_PLAYER)? MIN_SCORE:MAX_SCORE;
    int discRow ;
    int discCol ;
    int playscore;
    int newBoard[BOARD_SIZE][BOARD_SIZE];
    int board[BOARD_SIZE][BOARD_SIZE];

    /***/
    copyOriginalBoard(board);
    /***/

    std::vector<std::pair<int, int>> PossiblePositions = getPossiblePositions(player);

    /***/
    possiblePositions=PossiblePositions;
    /***/

    std::pair<int, int> bestPlay = std::make_pair(-1, -1);

    for (auto Position=begin(PossiblePositions); Position!=end(PossiblePositions) ; Position++)
    {
        discRow = Position->first;
        discCol = Position->second;

        copyBoard(board,newBoard);
        Update_ArrayForMinMax(newBoard,discRow,discCol,player);
        playscore = minMax(newBoard, (player == BLACK_PLAYER) ? WHITE_PLAYER : BLACK_PLAYER, depth - 1);

        if(player==BLACK_PLAYER)
        {	/* BLACK_PLAYER is maximizer (bestPlayScore is the highest score)*/
        if (playscore > bestPlayScore)
        {
            bestPlayScore = playscore;
            bestPlay = *Position;
        }
        else
        {
            /* Do Nothing */
        }
        }
        else
        {	/* WHITE_PLAYER is minimizer (bestPlayScore is the lowest score)*/
        if (playscore < bestPlayScore)
        {
            bestPlayScore = playscore;
            bestPlay = *Position;
        }
        else
        {
            /* Do Nothing */
        }
        }
    }
    return bestPlay;
}



int GameBoard::minMax(int board[BOARD_SIZE][BOARD_SIZE], int player, int depth)
{
    int bestPlayScore;
    int playScore;
    int discRow;
    int discCol;
    int newBoard[BOARD_SIZE][BOARD_SIZE];
    std::vector<std::pair<int, int>> PossiblePositions;
    if (depth == 0 || getPossiblePositionsForMinMax(board, player).empty()) {
        return evaluateBoard(board, BLACK_PLAYER);
    }
    else
    {
        /* Do Nothing */
    }

    /* BLACK_PLAYER is maximizer (initail score is INT_MIN),WHITE_PLAYER is minimizer(initail score is INT_MAX)  */
    bestPlayScore = (player==BLACK_PLAYER)? MIN_SCORE:MAX_SCORE;
    PossiblePositions = getPossiblePositionsForMinMax(board, player);
    for (auto Position=begin(PossiblePositions); Position!=end(PossiblePositions) ; Position++)
    {
        discRow = Position->first;
        discCol = Position->second;
        copyBoard(board,newBoard);
        Update_ArrayForMinMax(newBoard,discRow,discCol,player);
        playScore = minMax(newBoard, (player == BLACK_PLAYER)? WHITE_PLAYER:BLACK_PLAYER , depth - 1);

        if(player==BLACK_PLAYER)
        {	/* BLACK_PLAYER is maximizer (bestPlayScore is the highest score)*/
        bestPlayScore = (playScore > bestPlayScore)? playScore:bestPlayScore;
        }
        else
        {	/* WHITE_PLAYER is minimizer (bestPlayScore is the lowest score)*/
        bestPlayScore =(playScore < bestPlayScore)? playScore:bestPlayScore;
        }
    }

    return bestPlayScore;
}
