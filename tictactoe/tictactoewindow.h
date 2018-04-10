#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "tictactoe.h"
class QLabel;
class QWidget;
class QMenu;
class QAction;


class TictactoeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TictactoeWindow(QWidget *parent = 0);
    ~TictactoeWindow();

private:
    QLabel *m_player1Label;
	QLabel *m_player2Label;
	QWidget *m_mainWidget;
    TicTacToe *m_tictactoeWidget;
	QMenu *m_newMenu;
	QAction *m_startAction;
	QAction* m_quitAction;
	
	void createWidgets();
	void createLayouts();
    void createStyleSheets();
    void createConnections();
    void translateUi();

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
