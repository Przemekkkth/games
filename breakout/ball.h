#ifndef BALL_H
#define BALL_H
#include <QImage>
#include <QRect>
#include "../globalsettings.h"
class Ball
{
public:
    Ball();
    ~Ball();

    void resetState();
    void autoMove();
    void setXDir(int);
    void setYDir(int);
    int getXDir();
    int getYDir();
    QRect getRect();
    QImage& getImage();
private:
    int xdir;
    int ydir;
    QImage image;
    QRect rect;
    static const int INITIAL_X = (WIDTH/2)-30;//230 77% WIDTH
    static const int INITIAL_Y = (0.9*HEIGHT) - 10.;//350 90% HEIGHT - 10(wysokość piłki)
    static const int RIGHT_EDGE = WIDTH;//300 100% WIDTH
};

#endif // BALL_H
