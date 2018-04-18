#ifndef GAME_H
#define GAME_H
//game
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
    Snake *m_snake;
    TictactoeWindow *m_tictactoe;
    Breakout *m_breakout;
    GameMenu *m_gameMenu;
    Options *m_options;
    QStackedWidget *m_mainContent;


    void createWidgets();
    void createConnections();
    void translateUi();
    void createContainer();
    void createLayout();
    void createStyleSheet();
    void init();
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
