#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>
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
public:
    void setGame();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void drawObjects(QPainter*);
    void finishGame(QPainter*, QString);
    void moveObjects();

    void startGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();

private:
    int x;
    int timerId;
    static const int N_OF_BRICKS = 30;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = HEIGHT;//400
    static const int RIGHT_EDGE = WIDTH;//300
    Ball *ball;
    Paddle *paddle;
    Brick* bricks[N_OF_BRICKS];
    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;
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
