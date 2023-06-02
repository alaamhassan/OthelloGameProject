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

GameWindow::GameWindow(QWidget *parent, QString Player1Name, QString Player2Name, QStringList PlayerLevels) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{

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
        "border-radius:38px;"
        "border: 1px solid #1E3706;"
        "border-color:#1E3706;"

        "background-color:#90978E;"
        "color:#1E3706;"
        "}"
        ;

    ui->setupUi(this);

    gameBoard =new GameBoard();

    PlayerNamesList={Player1Name,Player2Name} ;
    InitializePlayerList(this);

    ui->graphicsView->setScene(gameBoard->GetBoardScene());

    ui->graphicsView->setMouseTracking(true);

    setMouseTracking(true);

    qDebug()<<"mouse:"<<(ui->graphicsView->hasMouseTracking());

    ui->graphicsView->show();


    ui->TurnLabel->setText(Player1Name+" Turn");

    ui->Player1->setText(Player1Name);
    ui->Player1Score->setText("2");

    ui->Player1R->setText(Player1Name);
    ui->player1RemindedPieces->setText("30");

    ui->Player2->setText(Player2Name);
    ui->Player2Score->setText("2");
    ui->Player2R->setText(Player2Name);
    ui->player2RemindedPieces->setText("30");

    ui->RestartButton->setStyleSheet(ButtonStyleSheet);
    ui->backButton->setStyleSheet(BackStyleSheet);

    ui->graphicsView->setStyleSheet("background-color:#000000;");

    //set the GameOver buttons (Restart,Menu) to not be visible
    ui->RestartButtonForGameOver->setVisible(false);
    ui->ReturnMenuForGameOver->setVisible(false);

    //set the GameOver label (message,finalScore) to not be visible
    ui->GameOverMessageLabel->setVisible(false);
    ui->FinalScoreGameOverLabel->setVisible(false);


    if((Player1Name.toStdString()).compare("Computer1")!=0)
    {
        ui->PlayGameButtonInCaseOfComputer->setVisible(false);
    }
    else
    {
        gameBoard->DisableBoard();
        ui->PlayGameButtonInCaseOfComputer->setStyleSheet(ButtonStyleSheet);
    }


}


GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/homePage/HomePage/GAMEWINDOW (2).png");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    QDialog::resizeEvent(event);
}

void GameWindow::setPlayerNamesList(QString Player1Name, QString Player2Name)
{
    PlayerNamesList={Player1Name,Player2Name};
}


void GameWindow::InitializePlayerList(QObject * GameWindow)
{
    gameBoard->setPlayerList(GameWindow,PlayerNamesList[0],PlayerNamesList[1]);
}



void GameWindow::RecievePlayerScoreUpdate(QStringList PlayerResponse)
{
    std::string ResponseTitle =PlayerResponse[0].toStdString();
    QString value =PlayerResponse[1];
    int PlayerNumber=0;

    if(ResponseTitle.compare("Update turn")==0)
    {
        ui->TurnLabel->setText(value+" Turn");
    }
    else if(ResponseTitle.compare("Player skip This Turn")==0)
    {
//messageBoxtoSkipTurn
    }


    qDebug()<<"Update Player Score: "<<value;

    if(ResponseTitle.compare("Update Player Score")==0)
    {
        qDebug()<<"Update Player Score: "<<value;

         PlayerNumber =PlayerResponse[2].toInt();

        if(PlayerNumber==0)ui->Player1Score->setText(value);

        else if(PlayerNumber==1)ui->Player2Score->setText(value);

    }
    else if(ResponseTitle.compare("Update Player Reminded Pieces")==0)
    {
        qDebug()<<"Update Player Reminded Pieces: "<<value;

        PlayerNumber =PlayerResponse[2].toInt();

        if(PlayerNumber==0)ui->player1RemindedPieces->setText(value);

        else if(PlayerNumber==1)ui->player2RemindedPieces->setText(value);
    }
//    else if(ResponseTitle.compare("Computer Play")==0)
//    {
//        gameBoard->DisableBoard();S
//    }
    else if(ResponseTitle.compare("GameOver")==0)
    {
        qDebug()<<"GameOver: "<<value;

        QString GameOverMessage=PlayerResponse[2];
        //disableButtons
        ui->RestartButton->setEnabled(false);
        ui->backButton->setEnabled(false);

        DisplayGameOver(GameOverMessage,value.toInt());
    }




}

void GameWindow::DisplayGameOver(QString Message,int GameFinalScore)
{

    //draw semi-transparent rect

    QGraphicsRectItem* transparentPanal =new QGraphicsRectItem(0,0,480,480);

    QBrush transparentbrush;
    transparentbrush.setStyle(Qt::SolidPattern);
    transparentbrush.setColor("#1E3706");
    transparentPanal->setBrush(transparentbrush);
    transparentPanal->setOpacity(0.43);
    gameBoard->GetBoardScene()->addItem(transparentPanal);


    QGraphicsRectItem* GameOverPanal =new QGraphicsRectItem(10,10,460,460);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor("#F1F1F1");
    GameOverPanal->setBrush(brush);
    GameOverPanal->setOpacity(0.75);
    gameBoard->GetBoardScene()->addItem(GameOverPanal);


    //set the GameOver buttons (Restart,Menu) to be visible
    ui->RestartButtonForGameOver->setVisible(true);
    ui->ReturnMenuForGameOver->setVisible(true);

    //set the style sheet of thebuttons
    ui->RestartButtonForGameOver->setStyleSheet(ButtonStyleSheet);
    ui->ReturnMenuForGameOver->setStyleSheet(ButtonStyleSheet);

    //show Text
    ui->GameOverMessageLabel->setVisible(true);
    ui->FinalScoreGameOverLabel->setVisible(true);

    //dispaly message
    ui->GameOverMessageLabel->setText(Message);
    ui->FinalScoreGameOverLabel->setText("Score: "+QString::number(GameFinalScore));


}

void GameWindow::on_RestartButton_clicked()
{
    QMessageBox::StandardButton replay =QMessageBox::question(this,"Restart"
                          ,"Are you sure you want to restart the game?",
                          QMessageBox::Yes|QMessageBox::No);

    if(replay==QMessageBox::Yes)
    {
        gameBoard =new GameBoard();
        InitializePlayerList(this);
        ui->graphicsView->setScene(gameBoard->GetBoardScene());

        ui->TurnLabel->setText(PlayerNamesList[0]+" Turn");
        ui->Player1Score->setText("2");
        ui->player1RemindedPieces->setText("30");
        ui->Player2Score->setText("2");
        ui->player2RemindedPieces->setText("30");


        if((PlayerNamesList[0].toStdString()).compare("Computer1")==0)
        {
            gameBoard->DisableBoard();
            gameBoard->computerPlay();
        }


    }

}


void GameWindow::on_backButton_clicked()
{
    QMessageBox::StandardButton replay =QMessageBox::question(this,"Back"
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


    gameBoard =new GameBoard();
    InitializePlayerList(this);
    ui->graphicsView->setScene(gameBoard->GetBoardScene());

    ui->TurnLabel->setText(PlayerNamesList[0]+" Turn");
    ui->Player1Score->setText("2");
    ui->player1RemindedPieces->setText("30");
    ui->Player2Score->setText("2");
    ui->player2RemindedPieces->setText("30");


    if((PlayerNamesList[0].toStdString()).compare("Computer1")==0)
    {
        gameBoard->DisableBoard();
        gameBoard->computerPlay();
    }
}


void GameWindow::on_ReturnMenuForGameOver_clicked()
{
    optionsWindow =new ModesWindow(this);
    optionsWindow->show();
    hide();
}


void GameWindow::on_PlayGameButtonInCaseOfComputer_clicked()
{
    ui->PlayGameButtonInCaseOfComputer->setVisible(false);
    gameBoard->computerPlay();
}

