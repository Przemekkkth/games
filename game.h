#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPaintEvent>
class Theme;
class Snake;
class TicTacToe;
class TictactoeWindow;
class Breakout;
class GameMenu;
class Options;

class QStackedWidget;



class Game: public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget* parent = 0);

private:
    Theme *m_theme;
    //1) m_Theme
    Snake *m_snake;
    //2) m_Snake
    TictactoeWindow *m_tictactoe;
    //3) tictactoe
    Breakout *m_breakout;
    //4) Breakout
    GameMenu *m_gameMenu;
    //5) game menu
    Options *m_options;
    //6) options

    //Kontener
    QStackedWidget *m_mainContent;


    void createWidgets();
    void createConnections();


private slots:
    void setGameMenuContent();
    void setSnakeContent();
    void setBreakoutContent();
    void setTicTacToeContent();
    void setThemeContent();
    void setOptionsContent();
protected:
    void paintEvent(QPaintEvent*);
};

#endif // GAME_H
