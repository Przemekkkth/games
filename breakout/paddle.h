#ifndef PADDLE_H
#define PADDLE_H
#include <QImage>
#include <QRect>
#include "../globalsettings.h"

class Paddle
{
public:
    Paddle();
    ~Paddle();
    QImage& getImage();
    QRect getRect();
    void move();
    void resetState();
    void setDx(int);

private:
    QImage image;
    QRect rect;
    int dx;
    static const int INITIAL_X = WIDTH / 2;//200 50% WIDTH/2
    static const int INITIAL_Y = 0.9 * HEIGHT;//360 90% HEIGHT
    static const int RIGHT_EDGE = WIDTH;//300 100% WIDTH
};

#endif // PADDLE_H
