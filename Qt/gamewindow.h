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
    explicit GameWindow(QWidget *parent = nullptr,QString Player1Name="",QString Player2Name="",int Player1Level=1,int Player2Level=1);
    ~GameWindow();

    void InitializePlayerList(QObject * GameWindow);
    void DisplayGameOver(QString Message,int GameFinalScore);
    void DrawPanalOnGraphicsScnene(std::array<int,4> RectDimentions,QString panalColor,float TransparancyDegree);
    void InitializeGameWindowLabels();
    void RestartGame();

public slots:
    void ReciveResponseFromThePlayer(QStringList);


protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_RestartButton_clicked();
    void on_backButton_clicked();

    void on_RestartButtonForGameOver_clicked();

    void on_ReturnMenuForGameOver_clicked();

    void on_PlayGameButtonInCaseOfComputer_clicked();


private:
    Ui::GameWindow *ui;

    QGraphicsScene* GameScene;
    QGraphicsRectItem* GameBoardRectangle;

    BoardSquare *boardSquare;
    GameBoard* gameBoard;


    QStringList PlayerNamesList;

    //int* PlayerLevels;

    int PlayerLevels[2]={1,1};

};

#endif // GAMEWINDOW_H
