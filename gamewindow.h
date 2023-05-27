#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "qgraphicsscene.h"
#include "gameboard.h"

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
    explicit GameWindow(QWidget *parent = nullptr,QString Player1Name="",QString Player2Name="",QStringList ={});
    ~GameWindow();
    void  setPlayerNamesList(QString Player1Name,QString Player2Name);
    void InitializePlayerList(QObject * GameWindow);

public slots:
    void RecievePlayerScoreUpdate(QStringList);
    void RecievePlayerRemindedPiecesUpdate(QStringList);
    void RecievePlayerWinOrLostUpdate(QStringList);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_RestartButton_clicked();
    void on_backButton_clicked();

private:
    Ui::GameWindow *ui;

    QGraphicsScene* GameScene;
    QGraphicsRectItem* GameBoardRectangle;

    BoardSquare *boardSquare;
    GameBoard* gameBoard;


    QStringList PlayerNamesList;

    bool isRestart=0;

};

#endif // GAMEWINDOW_H
