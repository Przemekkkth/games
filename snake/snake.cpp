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
    m_dot.load(":/images/dot");
    m_head.load(":/images/head");
    m_apple.load(":/images/apple");
}

void Snake::initGame()
{
    m_exitButton->hide();
    m_againButton->hide();
    m_inGame = true;
    m_paused = false;
    m_leftDirection = false;
    m_rightDirection = true;
    m_upDirection = false;
    m_downDirection = false;
    m_dots = 3;
    m_pointsLabel->setText(tr("Points : ")+QString::number((m_dots-3)*10));
    for(int z = 0; z < m_dots; z++)
    {
        m_x[z] = 50 - z * 10;
        m_y[z] = 50;
    }

    locateApple();

    m_timerId = startTimer(DELAY);
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

    if(m_inGame)
    {
        qp.drawImage(m_apple_x, m_apple_y , m_apple);

        for(int z = 0; z < m_dots; z++)
        {
            if(z == 0)
                qp.drawImage(m_x[z], m_y[z], m_head);
            else
            {
                qp.drawImage(m_x[z], m_y[z], m_dot);
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

    if(m_inGame)
    {
        return;
    }
}

void Snake::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if((key == Qt::Key_A) && (!m_rightDirection))
    {

        m_leftDirection = true;
        m_upDirection = false;
        m_downDirection = false;
    }

    if((key == Qt::Key_D) && (!m_leftDirection))
    {

        m_rightDirection = true;
        m_upDirection = false;
        m_downDirection = false;
    }

    if((key == Qt::Key_S) && (!m_upDirection))
    {
        m_downDirection = true;
        m_leftDirection = false;
        m_rightDirection = false;
    }

    if((key == Qt::Key_W) && (!m_downDirection))
    {
        m_upDirection = true;
        m_leftDirection = false;
        m_rightDirection = false;
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
    m_apple_x = (r*DOT_SIZE);

    r = qrand() % RAND_POS;
    m_apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *)
{
    if(m_inGame) {
            move();
            checkCollision();
            checkApple();

    }


    repaint();
}

void Snake::move()
{
    for(int z = m_dots; z > 0; z--)
    {
        m_x[z] = m_x[(z - 1)];
        m_y[z] = m_y[(z - 1)];
    }
    if(m_leftDirection)
    {
        m_x[0]-= DOT_SIZE;
    }
    if(m_rightDirection)
    {
        m_x[0] += DOT_SIZE;
    }
    if(m_upDirection)
    {
        m_y[0] -= DOT_SIZE;
    }
    if(m_downDirection)
    {
        m_y[0] += DOT_SIZE;
    }


}

void Snake::checkCollision()
{
    for(int z = m_dots; z > 0; z--)
    {
        if((z > 4) && (m_x[0] == m_x[z]) && (m_y[0]==m_y[z]))
        {
            m_inGame = false;
        }
    }
    m_pointsLabel->setText(tr("Points : ")+QString::number((m_dots-3)*10));
    if(m_x[0] > B_WIDTH)
    {
        m_inGame = false;
    }

    if(m_x[0] < 0)
    {
        m_inGame = false;
    }

    if(m_y[0] > B_HEIGHT)
    {
        m_inGame = false;
    }
    if(m_y[0] < 0)
    {
        m_inGame = false;
    }

    if(!m_inGame)
    {
        killTimer(m_timerId);
    }
}

void Snake::checkApple()
{
    if((m_x[0] == m_apple_x ) && (m_y[0] == m_apple_y))
    {
        m_dots++;
        locateApple();
    }
}

void Snake::stopGame()
{
    killTimer(m_timerId);
   // inGame = false;
}

void Snake::startGame()
{
    m_timerId = startTimer(DELAY);
    m_inGame = true;

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
        m_timerId = startTimer(DELAY);
        m_paused = false;
    }
    else
    {
        m_paused = true;
        killTimer(m_timerId);
    }
}
