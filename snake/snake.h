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
    QImage dot;
    QImage head;
    QImage apple;

    static const int B_WIDTH = 300;
    static const int B_HEIGHT = 300;
    static const int DOT_SIZE = 10;
    static const int ALL_DOTS = 900;
    static const int RAND_POS = 29;
    int DELAY = 140;

    int timerId;
    int dots;
    int apple_x;
    int apple_y;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;
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
