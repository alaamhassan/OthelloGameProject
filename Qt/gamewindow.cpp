#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "ModesWindow.h"
#include "computervscomputerwindow.h"
#include "computervspersonwindow.h"

#include <QGraphicsView>
#include<QDebug>
#include<QMessageBox>

ModesWindow *optionsWindow;
ComputerVsComputerWindow* computerVsComputerWindow;
ComputerVsPersonWindow* computerVsPersonWindow;
QString ButtonStyleSheet;


/*Initialize the gameWindow by providing:
 * Player1Name, Player2Name: which are provided by the user choice from the modesWindow.
 * PlayerLevels: which are provided by the user choice from the ComputerVsPerson or
 * ComputerVsComputerWindow.
 */
GameWindow::GameWindow(QWidget *parent, QString Player1Name, QString Player2Name, int Player1Level,int Player2Level) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

   /*----------------------creating the styleSheet for the buttons----------------------*/
    ButtonStyleSheet=
        "QPushButton{"
        "font-size:20px;"
        "border: 2px solid #1E3706;"
        "border-color:#1E3706;"
        "background-color:#E8E8E8;"
        "color:#1E3706;"
        "}"
        "QPushButton:hover{"
        "background-color:#1E3706;"
        "color:#E8E8E8;"
        "}"

        "QPushButton:pressed{"
        "background-color: #1E3706;"
        "color:#E8E8E8;"
        "}"
        ;

    QString BackStyleSheet=
        "QPushButton{"
        "font-size:30px;"
        "border-radius:10px;"
        "border: 2px solid #1E3706;"
        "border-color:#1E3706;"
        "background-color:#90978E;"
        "color:#1E3706;"
        "}"

        "QPushButton:hover{"
        "border-radius:10px;"
        "border: 2px solid #90978E;"
        "border-color:#90978E;"
        "background-color:#1E3706;"
        "color:#90978E;"
        "}"

        "QPushButton:pressed{"
        "border-radius:10px;"
        "border: 2px solid #90978E;"
        "border-color:#90978E;"
        "background-color:#1E3706;"
        "color:#90978E;"
        "}"
        ;

    QString PlayStyleSheet=
        "QPushButton{"
        "border: 4px solid #1E3706;"
        "border-color:#1E3706;"
        "background-color:#D9D9D9;"
        "color:#000000;"
        "}"

        "QPushButton:hover{"
        "border-color:#1E3706;"
        "background-color:#A6A6A6;"
        "color:#000000;"
        "}"

        "QPushButton:pressed{"
        "border-color:#1E3706;"
        "background-color:#A6A6A6;"
        "color:#000000;"
        "}"
        ;


   /*----------------------initializing varibales----------------------*/

   /*storing the palyer names in a list. which is used in initializaing the PlayerList
    * in the gameBoard class, and display the players information in the gameWindow.
    */
    PlayerNamesList={Player1Name,Player2Name} ;

    PlayerLevels[0]=Player1Level;
    PlayerLevels[1]=Player2Level;


   /*----------------------setting the baord scene and view----------------------*/

   /*initializing the gameBoard class, which has QGraphicsScene of the gameBoard.
    * the scene will be set to the graphicsView of the window.
    */
    gameBoard =new GameBoard();

   /*intiializing both the game players and storing them in a playerList variable, using
    * setPlayerList() function in gameBoard class.
    * this palyerList is used in the gameBoard class to manage the two palyers.
    * -->this keyword where passed to be able to establish a connection between the two palyers
    * and the gameWindow class.
    */
    InitializePlayerList(this);

    /*setting the graphicsView scene*/
    ui->graphicsView->setScene(gameBoard->GetBoardScene());

    /*enable events triggering for mouse events on the scene (ex: player press a square)*/
    ui->graphicsView->setMouseTracking(true);

    /*display the board to the user*/
    ui->graphicsView->show();


    /*----------------------setting gameWindow labels----------------------*/

    ui->Player1->setText(Player1Name);
    ui->Player1R->setText(Player1Name);

    ui->Player2->setText(Player2Name);
    ui->Player2R->setText(Player2Name);

   /*setting current player turn, score, and reminded pieces for the two players.
    * the initialization was done in the functions, for reusing the code when restarting
    * the game. Instead of writing the same code again in many places (code reusability).
    */
    InitializeGameWindowLabels();


    /*----------------------setting gameWindow styleSheets----------------------*/

    ui->RestartButton->setStyleSheet(ButtonStyleSheet);
    ui->backButton->setStyleSheet(BackStyleSheet);

    ui->graphicsView->setStyleSheet("background-color:#000000;");


    /*----------------------disable visiblity for some gameWindow parts----------------------*/

   /*the following parts will only be visible when game is over and gameOver panal is displayed,
    * in DisplayGameOver() function in the gameWindow class.
    */

    /*set the GameOver buttons (Restart,Menu) to not be visible.*/
    ui->RestartButtonForGameOver->setVisible(false);
    ui->ReturnMenuForGameOver->setVisible(false);

    /*set the GameOver label (message,finalScore) to not be visible*/
    ui->GameOverMessageLabel->setVisible(false);
    ui->FinalScoreGameOverLabel->setVisible(false);


    /*----------------------setting the gameWindow in case (ComputerVSComputer)----------------------*/

    /*checking if the current players where only computers (ComputerVSComputer) window*/

   /*1.if it's not:
    * then:
    * set the play button (which is only shown in case of ComputerVSComputer window) to not be visible.
    * the play button is created for user convenience, so that the game will not start
    * as soon as the player enter the gameWindow, but when the play button is pressed.
    * note: the Player1Name was converted to a String to use compare() function, and equivilince, as
    * QString doesn't suport the two (as far as I know).
    */

    if((Player1Name.toStdString()).compare("Computer1")!=0)
    {
        ui->PlayGameButtonInCaseOfComputer->setVisible(false);
    }

    /*2.if it's:*/
    else
    {
       /*2.1) disable the gameBoard by disable mouse tracking, as the two computers
        * are going to play the game without human intervention, the board is disable
        * to not trigger any mouse press events from the user.
        */
        gameBoard->DisableBoard();

       /*2.2) disable (Restart) buttons. as the game will not start until the user press the play
        * button. there is no meaning in restarting the game, when it didn't even start!.
        * the button will be enabled when the user hit the play button in
        * on_PlayGameButtonInCaseOfComputer_clicked() event in the gameWindow class.
        */
        ui->RestartButton->setEnabled(false);

       /*2.3) set the styleSheet of the playButton.
        * the styling was done here, as in any other case than the (ComputerVSComputer window)
        * the button will not be visible.
        */
        ui->PlayGameButtonInCaseOfComputer->setStyleSheet(PlayStyleSheet);
    }


}


GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/gameWindow/HomePage/gameWindowUpdated.png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    QDialog::resizeEvent(event);
}



/*setting the playerList in the gameBoard class, which contains two object of the Player class.
 * -->the GameWindow where passed to be able to establish a connection between the two palyers
 * and the gameWindow class.
 */
void GameWindow::InitializePlayerList(QObject * GameWindow)
{
    gameBoard->setPlayerList(GameWindow,PlayerNamesList[0],PlayerNamesList[1],PlayerLevels);
}

/*this function is used to draw a panal on the gameWindow graphics scene, by providing:
 * 1) RectDimentions: array containing four elements :
 *    1,2: top-left corner coordinate (x_coordinate,y_coordinate).
 *    3,4: width and hight of the panal.
 * 2) panalColor: the panal color.
 * 3) TransparancyDegree: a float number from (0->1), indicating the transparancy of the panal,
 *    1:not transparent, 0:full transparent.
 * --------------------------------------------------------------------------------------
 * this function is used when displaying the gameOver panal in DisplayGameOver() function in gameWindow class.
 */
void GameWindow::DrawPanalOnGraphicsScnene(std::array<int,4> RectDimentions,QString panalColor,float TransparancyDegree)
{
    QGraphicsRectItem* TransparentPanal =new QGraphicsRectItem(RectDimentions[0],RectDimentions[1],RectDimentions[2],RectDimentions[3]);
    QBrush Transparentbrush;

    Transparentbrush.setStyle(Qt::SolidPattern);
    Transparentbrush.setColor(panalColor);
    TransparentPanal->setBrush(Transparentbrush);
    TransparentPanal->setOpacity(TransparancyDegree);


    /*adding the new panal to the gameBoard scene.*/
    gameBoard->GetBoardScene()->addItem(TransparentPanal);
}

/*setting current player turn, score, and reminded pieces for the two players.
* the initialization was done in the functions, for reusing the code when intializing, and
* restarting the game. Instead of writing the same code again in many places (code reusability).
*/
void GameWindow::InitializeGameWindowLabels()
{
    ui->TurnLabel->setText(PlayerNamesList[0]+" Turn");
    ui->Player1Score->setText("2");
    ui->player1RemindedPieces->setText("30");
    ui->Player2Score->setText("2");
    ui->player2RemindedPieces->setText("30");
}

/*This functions takes a signal from the player class (two objects in the PlayerList in the gameBoard class),
 * when a player press a square, the player functions like (updateScore, updateRemindedPieces,..) is called
 * in the gameBoard class. These functions send a signal to the this function.
 *-------------------------------------------------------------------------------
 * this function is used update the game status (score, remindedPieces, isGameOver,..)
 */
void GameWindow::ReciveResponseFromThePlayer(QStringList PlayerResponse)
{

    /*the ResponseTitle is the title of the message, which changes based on the event.*/
    std::string ResponseTitle =PlayerResponse[0].toStdString();

    /*value is the the body of the message, it differes (type, and value ) based on the event*/
    QString value =PlayerResponse[1];


   /*1. in case of --> update turn event:
    * update the current player turn on the window.
    */
    if(ResponseTitle.compare("Update turn")==0)
    {
        ui->TurnLabel->setText(value+" Turn");
    }

   /*2. in case of --> when a player doesn't have any valid move
    * for this turn:
    * a skip message will be displayed
    * do it:########################################################################################################
    */
    else if(ResponseTitle.compare("Player skip This Turn")==0)
    {
        QMessageBox::StandardButton skip =
            QMessageBox::information(this,"skip"
                                  ,value+" will skip this turn",
                                  QMessageBox::Yes);
    }

   /*3.in case of -->update player score event:
    * parse the second place in the PlayerRespone, which is the playerIndex (0 or 1).
    * update the score of this player on the gameWindow.
    */
   else if(ResponseTitle.compare("Update Player Score")==0)
    {

        int PlayerNumber =PlayerResponse[2].toInt();

        if(PlayerNumber==0)ui->Player1Score->setText(value);

        else if(PlayerNumber==1)ui->Player2Score->setText(value);

    }

   /*4.in case of -->update player remindedPieces event:
    * parse the second place in the PlayerRespone, which is the playerIndex (0 or 1).
    * update the reminded pieces of this player on the gameWindow.
    */
    else if(ResponseTitle.compare("Update Player Reminded Pieces")==0)
    {

        int PlayerNumber =PlayerResponse[2].toInt();

        if(PlayerNumber==0)ui->player1RemindedPieces->setText(value);

        else if(PlayerNumber==1)ui->player2RemindedPieces->setText(value);
    }

   /*4.in case of -->gameOver event:
    * parse the second place in the PlayerRespone, which is the gameOver message
    * (Draw, player win).
    */
    else if(ResponseTitle.compare("GameOver")==0)
    {

        QString GameOverMessage=PlayerResponse[2];

       /*the (restart, back) button will be disabled, as when game is over
        * a panal will appear containing two buttons (menu, restart).
        * These buttons are the only options for the user when game is over.
        */
        ui->RestartButton->setEnabled(false);
        ui->backButton->setEnabled(false);

       /*display the game over panal, which contains:
        * 1.the gameOver message (Draw, player Win).
        * 2.the final score of the game winner in case of win, or the score if draw.
        * 3.restart and menu buttons.
        */
        DisplayGameOver(GameOverMessage,value.toInt());
    }

    else if(ResponseTitle.compare("Player will take a piece from opponent")==0)
    {
        QString otherPlayerName="";

        if(PlayerNamesList[0]!=value)otherPlayerName=PlayerNamesList[0];
        else
            otherPlayerName=PlayerNamesList[1];

        QMessageBox::StandardButton takePiecesFromOpponent =
            QMessageBox::information(this,"TakePiecesFromOpponent"
                                     ,value+" will take a piece from "+otherPlayerName,
                                     QMessageBox::Yes);
    }
}

/* this function is used when the game is over to display the game over panal,
* which takes:
* Message: the gameOver message (Draw, player Win).
* GameFinalScore: thefinal score of the game winner in case of win, or the score if draw.
*/
void GameWindow::DisplayGameOver(QString Message,int GameFinalScore)
{

   /*draw semi-transparent panal by providing:
    * 1) RectDimentions: array containing four elements :
    *    1,2: top-left corner coordinate (x_coordinate,y_coordinate).
    *    3,4: width and hight of the panal.
    *    ---->{0,0,480,480}
    * 2) panalColor: the panal color.
    *    ---->#1E3706
    * 3) TransparancyDegree: a float number from (0->1), indicating the transparancy of the panal,
    *    1:not transparent, 0:full transparent.
    *    ---->0.43
    */
    DrawPanalOnGraphicsScnene({0,0,480,480},"#1E3706",0.43);

    /*draw GameOver panal by providing:
    * 1) RectDimentions: array containing four elements :
    *    1,2: top-left corner coordinate (x_coordinate,y_coordinate).
    *    3,4: width and hight of the panal.
    *    ---->{10,10,460,460}.
    * 2) panalColor: the panal color.
    *    ---->#F1F1F1.
    * 3) TransparancyDegree: a float number from (0->1), indicating the transparancy of the panal,
    *    1:not transparent, 0:full transparent.
    *    ---->0.75.
    */
    DrawPanalOnGraphicsScnene({10,10,460,460},"#F1F1F1",0.75);

    /*set the GameOver buttons (Restart,Menu) to be visible*/
    ui->RestartButtonForGameOver->setVisible(true);
    ui->ReturnMenuForGameOver->setVisible(true);

    /*set the style sheet of the buttons*/
    ui->RestartButtonForGameOver->setStyleSheet(ButtonStyleSheet);
    ui->ReturnMenuForGameOver->setStyleSheet(ButtonStyleSheet);

    /*show the gameOver message label to the user, and set it's text to "Message"*/
    ui->GameOverMessageLabel->setVisible(true);
    ui->GameOverMessageLabel->setAlignment(Qt::AlignCenter);
    ui->GameOverMessageLabel->setText(Message);

   /*show the finalScore label to the user, and set it's text to
    * "Score" + ("GameFinalScore" after converting it to a QString).
    */
    ui->FinalScoreGameOverLabel->setVisible(true);
    ui->FinalScoreGameOverLabel->setText("Score: "+QString::number(GameFinalScore));
}


void GameWindow::RestartGame()
{
    gameBoard =new GameBoard();
    InitializePlayerList(this);
    ui->graphicsView->setScene(gameBoard->GetBoardScene());

    InitializeGameWindowLabels();

    if((PlayerNamesList[0].toStdString()).compare("Computer1")==0)
    {
        gameBoard->DisableBoard();
        gameBoard->computerPlay();
    }
}



//slots::

void GameWindow::on_RestartButton_clicked()
{
    QMessageBox::StandardButton replay =
        QMessageBox::question(this,"Restart"
        ,"Are you sure you want to restart the game?",
        QMessageBox::Yes|QMessageBox::No);

    if(replay==QMessageBox::Yes)
    {
        RestartGame();
    }

}


void GameWindow::on_backButton_clicked()
{
    QMessageBox::StandardButton replay =
        QMessageBox::question(this,"Back"
        ,"You will lose your progress if you clicked back!",
        QMessageBox::Yes|QMessageBox::No);

    if(replay==QMessageBox::Yes)
    {
        if(PlayerNamesList[0]=="Player1")
        {
            optionsWindow =new ModesWindow(this);
            optionsWindow->show();
            hide();
        }
        else if (PlayerNamesList[0]=="Player")
        {
            computerVsPersonWindow =new ComputerVsPersonWindow();
            computerVsPersonWindow->show();
            hide();

        }
        else if (PlayerNamesList[0]=="Computer1")
        {
            computerVsComputerWindow = new ComputerVsComputerWindow();
            computerVsComputerWindow->show();
            hide();
        }


    }

}

void GameWindow::on_RestartButtonForGameOver_clicked()
{
    //set the GameOver buttons (Restart,Menu) to not be visible
    ui->RestartButtonForGameOver->setVisible(false);
    ui->ReturnMenuForGameOver->setVisible(false);

    //set the GameOver label (message,finalScore) to not be visible
    ui->GameOverMessageLabel->setVisible(false);
    ui->FinalScoreGameOverLabel->setVisible(false);

    //enable (Restart,back) buttons
    ui->RestartButton->setEnabled(true);
    ui->backButton->setEnabled(true);

    //Restart the game
    RestartGame();

}



void GameWindow::on_ReturnMenuForGameOver_clicked()
{
    optionsWindow =new ModesWindow(this);
    hide();
    optionsWindow->show();

}


void GameWindow::on_PlayGameButtonInCaseOfComputer_clicked()
{
    ui->PlayGameButtonInCaseOfComputer->setVisible(false);

    //enable (Restart) buttons
    ui->RestartButton->setEnabled(true);

    gameBoard->computerPlay();


}


