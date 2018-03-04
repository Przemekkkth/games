#include "paddle.h"
#include <iostream>

Paddle::Paddle()
{
    dx = 0;
    image.load(":/images/paddle");
    rect = image.rect();
    resetState();
}

Paddle::~Paddle()
{

}

void Paddle::setDx(int x)
{
    dx = x;
}

void Paddle::move()
{
    int x = rect.x() + dx;
    int y = rect.top();
    if(x+rect.width() > RIGHT_EDGE){
        x-= (rect.width()/8);
    }
    if(x < 0)
    {
        x+=(rect.width()/8);
    }
    rect.moveTo(x, y);
}

void Paddle::resetState()
{
    rect.moveTo(INITIAL_X-rect.width(), INITIAL_Y);
}

QRect Paddle::getRect()
{
    return rect;
}

QImage& Paddle::getImage()
{
    return image;
}
