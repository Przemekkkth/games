#include "brick.h"
#include <iostream>

Brick::Brick(int x, int y)
{
    m_image.load(":/images/brickie");
    m_destroyed = false;
    m_rect = m_image.rect();
    m_rect.translate(x, y);
}

Brick::~Brick()
{

}

QRect Brick::getRect()
{
    return m_rect;
}

void Brick::setRect(QRect rct)
{
    m_rect = rct;
}

QImage& Brick::getImage()
{
    return m_image;
}

bool Brick::isDestroyed()
{
    return m_destroyed;
}

void Brick::setDestroyed(bool destr)
{
    m_destroyed = destr;
}
