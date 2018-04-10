#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>

class QPushButton;

class GameMenu : public QWidget
{
    Q_OBJECT
public:
    explicit GameMenu(QWidget *parent = 0);
protected:
    void changeEvent(QEvent*);
signals:
    void tictactoeClicked();
    void arcanoidClicked();
    void snakeClicked();
    void backtomenuClicked();
public slots:
    void clickTicTacToe();
    void clickArcanoid();
    void clickSnake();
    void clickBackToMenu();
private:
    QPushButton *m_TicTacToeButton,
                *m_ArcanoidButton,
                *m_SnakeButton,
                *m_BackToMenuButton;

    void createConnections();
    void createWidgets();
    void createLayout();
    void createStyleSheet();
    void translateUi();

};

#endif // GAMEMENU_H
