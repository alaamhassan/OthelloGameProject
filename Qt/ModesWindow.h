#ifndef MODESWINDOW_H
#define MODESWINDOW_H

#include <QDialog>
#include <QMainWindow>

#include "gamewindow.h"
#include "computervspersonwindow.h"
#include "computervscomputerwindow.h"

namespace Ui {
class ModesWindow;
}

class ModesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModesWindow(QWidget *parent = nullptr);
    void InitializeComputerLevelsMap();
    ~ModesWindow();


protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_backButton_clicked();

    void on_MinMaxButton_clicked();

    void on_BetaAlphaButton_clicked();

    void on_BettaAlphaIterativeButton_clicked();

private:
    Ui::ModesWindow *ui;
    GameWindow* gameWindow;
    ComputerVsPersonWindow* computerVsPersonWindow;
    ComputerVsComputerWindow* computerVsComputerWindow;
    std::map<QString,int>ComputerLevelsMap;
};

#endif // MODESWINDOW_H
