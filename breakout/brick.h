#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>

class Brick
{
public:
    Brick(int , int);
    ~Brick();
public:
    QImage& getImage();
    QRect getRect();
    bool isDestroyed();
    void setDestroyed(bool);    
    void setRect(QRect);

private:
    QImage m_image;
    QRect m_rect;
    bool m_destroyed;
};

#endif // BRICK_H
