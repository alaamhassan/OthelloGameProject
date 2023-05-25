#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "qgraphicsscene.h"
#include "gameboard.h"
#include "player.h"

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include<QDebug>


namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr,QString Player1Name="",QString Player2Name="");
    ~GameWindow();
    void  setPlayerNamesList(QString Player1Name,QString Player2Name);
    void InitializePlayerList(QObject * GameWindow);

public slots:
    void RecievePlayerScoreUpdate(QStringList);
    void RecievePlayerRemindedPiecesUpdate(QStringList);
    void RecievePlayerWinOrLostUpdate(QStringList);

   // void RecievePlayerTurnFromGameBoard(QString Playerturn);

private:
    Ui::GameWindow *ui;

    QGraphicsScene* GameScene;
    QGraphicsRectItem* GameBoardRectangle;

    BoardSquare *boardSquare;
    GameBoard* gameBoard;
  //  Player* playerList[2];

    QStringList PlayerNamesList;

};

#endif // GAMEWINDOW_H
