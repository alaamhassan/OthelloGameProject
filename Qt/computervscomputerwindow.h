#ifndef COMPUTERVSCOMPUTERWINDOW_H
#define COMPUTERVSCOMPUTERWINDOW_H

#include <QDialog>
#include "gamewindow.h"

namespace Ui {
class ComputerVsComputerWindow;
}

class ComputerVsComputerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerVsComputerWindow(QWidget *parent = nullptr);
    void InitializeComputerLevelsMap();
    ~ComputerVsComputerWindow();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_backButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::ComputerVsComputerWindow *ui;
    GameWindow* gameWindow;
    std::map<QString,int> ComputerLevelsMap;
};

#endif // COMPUTERVSCOMPUTERWINDOW_H
