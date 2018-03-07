#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tictactoe.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TictactoeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TictactoeWindow(QWidget *parent = 0);
    ~TictactoeWindow();

private:
    Ui::MainWindow *ui;
public slots:

    void startNewGame();
private slots:
    void updateNameLabels();
    void handleGameOver(TicTacToe::Player);
    void goBack();
signals:
    void backtomenuClicked();
};

#endif // MAINWINDOW_H
