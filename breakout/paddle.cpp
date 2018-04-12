#include "paddle.h"
#include <iostream>

Paddle::Paddle()
{
    m_dx = 0;
    m_image.load(":/images/paddle");
    m_rect = m_image.rect();
    resetState();
}

Paddle::~Paddle()
{

}

void Paddle::setDx(int x)
{
    m_dx = x;
}

void Paddle::move()
{
    int x = m_rect.x() + m_dx;
    int y = m_rect.top();
    if(x+m_rect.width() > RIGHT_EDGE){
        x-= (m_rect.width()/8);
    }
    if(x < 0)
    {
        x+=(m_rect.width()/8);
    }
    m_rect.moveTo(x, y);
}

void Paddle::resetState()
{
    m_rect.moveTo(INITIAL_X-m_rect.width(), INITIAL_Y);
}

QRect Paddle::getRect()
{
    return m_rect;
}

QImage& Paddle::getImage()
{
    return m_image;
}
