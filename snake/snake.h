#ifndef SNAKE_H
#define SNAKE_H

#include <QKeyEvent>
#include <QLabel>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimerEvent>
#include <QWidget>

#include "globalsettings.h"

class Snake : public QWidget
{
    Q_OBJECT

public:
    Snake(QWidget *parent = 0);
    ~Snake();
    void stopGame();
    void startGame();
    void setGame();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    QImage m_dot;
    QImage m_head;
    QImage m_apple;

    static const int B_WIDTH = 300;
    static const int B_HEIGHT = 300;
    static const int DOT_SIZE = 10;
    static const int ALL_DOTS = 900;
    static const int RAND_POS = 29;
    int DELAY = 140;

    int m_timerId;
    int m_dots;
    int m_apple_x;
    int m_apple_y;

    int m_x[ALL_DOTS];
    int m_y[ALL_DOTS];

    bool m_leftDirection;
    bool m_rightDirection;
    bool m_upDirection;
    bool m_downDirection;
    bool m_inGame;
    bool m_paused;

    void loadImages();
    void initGame();
    void locateApple();
    void checkApple();
    void checkCollision();
    void move();
    void doDrawing();
    void pauseGame();
    void gameOver(QPainter& );

    QPushButton *m_againButton;
    QPushButton *m_exitButton;
    QLabel *m_pointsLabel;

    void createButtons();

signals:
    void exitClicked();
private slots:
    void againGame();
    void exitGame();

};

#endif // SNAKE_H
