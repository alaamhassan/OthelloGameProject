#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "qgraphicsscene.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    QGraphicsScene* GameScene;
    َQGraphicsRectItem* GameBoardRectangle ;

};

#endif // GAMEWINDOW_H
