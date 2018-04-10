#include "ball.h"
#include <iostream>
#include <QDebug>

Ball::Ball()
{
    m_xdir = 1;
    m_ydir = -1;

    m_image.load(":/images/ball");

    m_rect = m_image.rect();
    resetState();

}

Ball::~Ball()
{
   
}

void Ball::autoMove()
{
   m_rect.translate(m_xdir, m_ydir);
   if(m_rect.left() == 0)
   {
       m_xdir = 1;
   }
   if(m_rect.right() == RIGHT_EDGE)
   {
       m_xdir = -1;
   }

    if(m_rect.top() == 0)
    {
        m_ydir = 1;
    }
}

void Ball::resetState()
{
    m_rect.moveTo(INITIAL_X, INITIAL_Y);

}

void Ball::setXDir(int x)
{
    m_xdir = x;
}

void Ball::setYDir(int y)
{
    m_ydir = y;
}

int Ball::getXDir()
{
    return m_xdir;
}

int Ball::getYDir()
{
    return m_ydir;
}

QRect Ball::getRect()
{
    return m_rect;
}

QImage & Ball::getImage()
{
    return m_image;
}
