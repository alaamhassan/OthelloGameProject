#ifndef COMPUTERVSCOMPUTERWINDOW_H
#define COMPUTERVSCOMPUTERWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include "gamewindow.h"

namespace Ui {
class ComputerVsComputerWindow;
}

class ComputerVsComputerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerVsComputerWindow(QWidget *parent = nullptr);
    ~ComputerVsComputerWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_backButton_clicked();

    void on_nextButton_clicked();

    void on_MinMaxButton_clicked();

    void on_BetaAlphaButton_clicked();

    void on_BettaAlphaIterativeButton_clicked();

private:
    Ui::ComputerVsComputerWindow *ui;
    GameWindow* gameWindow;
};

#endif // COMPUTERVSCOMPUTERWINDOW_H
