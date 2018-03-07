#include "snake.h"
#include <QPainter>
#include <QTime>
#include <QMessageBox>
#include <QDebug>

Snake::Snake(QWidget *parent)
    : QWidget(parent)
{

    createButtons();
    QFont font("Courier", 15, QFont::DemiBold);
    m_pointsLabel = new QLabel(this);
    m_pointsLabel->resize(B_WIDTH, 25);
    m_pointsLabel->setAlignment(Qt::AlignRight);
    m_pointsLabel->setFont(font);
    m_pointsLabel->setGeometry(0, B_HEIGHT, B_WIDTH, 25);
    m_pointsLabel->setStyleSheet("border-top: 1px solid red");

    setStyleSheet("background-color: black; color: white;");



    resize(B_WIDTH, B_HEIGHT + 25);
    loadImages();
    initGame();

    stopGame();
}

Snake::~Snake()
{

}

void Snake::loadImages()
{
    dot.load(":/images/dot");
    head.load(":/images/head");
    apple.load(":/images/apple");
}

void Snake::initGame()
{
    m_exitButton->hide();
    m_againButton->hide();
    inGame = true;
    m_paused = false;
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    dots = 3;
    m_pointsLabel->setText(tr("Punkty : ")+QString::number((dots-3)*10));
    for(int z = 0; z < dots; z++)
    {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    locateApple();

    timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *)
{
    doDrawing();
}

void Snake::doDrawing()
{

    QPainter qp(this);
    qp.setBrush(QBrush(Qt::black));
    qp.drawRect(-10, -10 , rect().width() + 10, rect().height() + 10);

    if(inGame)
    {
        qp.drawImage(apple_x, apple_y , apple);

        for(int z = 0; z < dots; z++)
        {
            if(z == 0)
                qp.drawImage(x[z], y[z], head);
            else
            {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    }
    else
    {
        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp)
{
    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
    qp.drawText(-textWidth, fm.height() + 2, tr("Do you want again?") );

    m_againButton->show();
    m_againButton->setGeometry(w/2, h/2 + 2* fm.height() + 2, 40, 20);

    m_exitButton->show();
    m_exitButton->setGeometry(w/2 + 40, h/2 + 2* fm.height() + 2, 40, 20);

    if(inGame)
    {
        return;
    }
}

void Snake::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if((key == Qt::Key_A) && (!rightDirection))
    {

        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if((key == Qt::Key_D) && (!leftDirection))
    {

        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if((key == Qt::Key_S) && (!upDirection))
    {
        downDirection = true;
        leftDirection = false;
        rightDirection = false;
    }

    if((key == Qt::Key_W) && (!downDirection))
    {
        upDirection = true;
        leftDirection = false;
        rightDirection = false;
    }


    if(key == Qt::Key_P)
    {
        pauseGame();
    }



    if(key == Qt::Key_Backspace)
    {
        exitGame();

    }
    QWidget::keyPressEvent(event);
}

void Snake::locateApple()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r*DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *)
{
    if(inGame) {
            move();
            checkCollision();
            checkApple();

    }


    repaint();
}

void Snake::move()
{
    for(int z = dots; z > 0; z--)
    {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }
    if(leftDirection)
    {
        x[0]-= DOT_SIZE;
    }
    if(rightDirection)
    {
        x[0] += DOT_SIZE;
    }
    if(upDirection)
    {
        y[0] -= DOT_SIZE;
    }
    if(downDirection)
    {
        y[0] += DOT_SIZE;
    }


}

void Snake::checkCollision()
{
    for(int z = dots; z > 0; z--)
    {
        if((z > 4) && (x[0] == x[z]) && (y[0]==y[z]))
        {
            inGame = false;
        }
    }
    m_pointsLabel->setText(tr("Punkty : ")+QString::number((dots-3)*10));
    if(x[0] > B_WIDTH)
    {
        inGame = false;
    }

    if(x[0] < 0)
    {
        inGame = false;
    }

    if(y[0] > B_HEIGHT)
    {
        inGame = false;
    }
    if(y[0] < 0)
    {
        inGame = false;
    }

    if(!inGame)
    {
        killTimer(timerId);
    }
}

void Snake::checkApple()
{
    if((x[0] == apple_x ) && (y[0] == apple_y))
    {
        dots++;
        locateApple();
    }
}

void Snake::stopGame()
{
    killTimer(timerId);
   // inGame = false;
}

void Snake::startGame()
{
    timerId = startTimer(DELAY);
    inGame = true;

}


void Snake::createButtons()
{
    m_againButton = new QPushButton(this);
    m_againButton->setText(tr("Yes"));
    m_againButton->setFont(QFont("Courier", 15, QFont::DemiBold));
    m_againButton->setDefault(false);
    m_againButton->setAutoDefault(false);
    m_againButton->setFocusPolicy(Qt::NoFocus);

    m_againButton->hide();
    m_againButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_exitButton = new QPushButton(this);
    m_exitButton->setText(tr("No"));
    m_exitButton->setFont(QFont("Courier", 15, QFont::DemiBold));
    m_exitButton->setDefault(false);
    m_exitButton->setAutoDefault(false);
    m_exitButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_exitButton->setFocusPolicy(Qt::NoFocus);
    m_exitButton->hide();


    connect(m_againButton, SIGNAL(clicked(bool)), this, SLOT(againGame()));
    connect(m_exitButton, SIGNAL(clicked(bool)), this, SLOT(exitGame()));
}

void Snake::exitGame()
{

    stopGame();
    emit exitClicked();

}

void Snake::againGame()
{
   initGame();
}

void Snake::setGame()
{
    initGame();
}

void Snake::pauseGame()
{
    if(m_paused)
    {
        timerId = startTimer(DELAY);
        m_paused = false;
    }
    else
    {
        m_paused = true;
        killTimer(timerId);
    }
}
