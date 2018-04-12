#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include "../globalsettings.h"

class Breakout : public QWidget
{
    Q_OBJECT
public:
    explicit Breakout(QWidget *parent = 0);
    ~Breakout();
    void setGame();

protected:
    void drawObjects(QPainter*);
    void finishGame(QPainter*, QString);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void paintEvent(QPaintEvent*);
    void moveObjects();
    void timerEvent(QTimerEvent*);

    void checkCollision();
    void pauseGame();
    void startGame();
    void stopGame();
    void victory();
//nizeje jest nieposortowane
private:
    int m_x;
    int m_timerId;
    static const int N_OF_BRICKS = 30;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = HEIGHT;//400
    static const int RIGHT_EDGE = WIDTH;//300
    Ball *m_ball;
    Paddle *m_paddle;
    Brick* m_bricks[N_OF_BRICKS];
    bool m_gameOver;
    bool m_gameWon;
    bool m_gameStarted;
    bool m_paused;
    void createButtons();
    QPushButton *m_againButton;
    QPushButton *m_exitButton;
    QLabel *m_pointsLabel;
    void initGame();

signals:
    void exitClicked();

private slots:
    void exitGame();
    void againGame();
};

#endif // BREAKOUT_H
