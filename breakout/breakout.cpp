#include <QPainter>
#include <QApplication>
#include "breakout.h"
#include <QMessageBox>
#include <iostream>

Breakout::Breakout(QWidget *parent)
    : QWidget(parent) {
  createButtons();
  resize(RIGHT_EDGE, BOTTOM_EDGE);
  setStyleSheet("QWidget{background-color: black; color: white;}");
  initGame();
  m_ball = new Ball();
  m_paddle = new Paddle();

  int k = 0;

  for (int i=0; i<5; i++) {
    for (int j=0; j<6; j++) {
      m_bricks[k] = new Brick(j*40+30, i*16+60);
      k++;
    }
  }
}

Breakout::~Breakout() {

 delete m_ball;
 delete m_paddle;

 for (int i=0; i<N_OF_BRICKS; i++) {
   delete m_bricks[i];
 }
}

void Breakout::paintEvent(QPaintEvent *e) {

  Q_UNUSED(e);

  QPainter painter(this);

  if (m_gameOver) {

    finishGame(&painter, "Game lost");

  } else if(m_gameWon) {

    finishGame(&painter, "Victory");
  }
  else {

    drawObjects(&painter);
  }
}

void Breakout::finishGame(QPainter *painter, QString message) {

  QFont font("Courier", 15, QFont::DemiBold);
  QFontMetrics fm(font);
  int textWidth = fm.width(message);

  painter->setFont(font);
  int h = height();
  int w = width();

  painter->translate(QPoint(w/2, h/2));
  painter->drawText(-textWidth/2, 0, message);
  painter->drawText(-textWidth, fm.height() + 2, tr("Do you want again?"));

  m_againButton->show();
  m_againButton->setGeometry(w/2, h/2 + 2* fm.height() + 2, 40, 20);

  m_exitButton->show();
  m_exitButton->setGeometry(w/2 + 40, h/2 + 2* fm.height() + 2, 40, 20);


}

void Breakout::drawObjects(QPainter *painter) {

  painter->drawImage(m_ball->getRect(), m_ball->getImage());
  painter->drawImage(m_paddle->getRect(), m_paddle->getImage());

  for (int i=0; i<N_OF_BRICKS; i++) {
    if (!m_bricks[i]->isDestroyed()) {
      painter->drawImage(m_bricks[i]->getRect(), m_bricks[i]->getImage());
    }
  }
}

void Breakout::timerEvent(QTimerEvent *e) {

  Q_UNUSED(e);

  moveObjects();
  checkCollision();
  repaint();
}

void Breakout::moveObjects() {

  m_ball->autoMove();
  m_paddle->move();
}

void Breakout::keyReleaseEvent(QKeyEvent *e) {

    int dx = 0;

    switch (e->key()) {
        case Qt::Key_A:
            dx = 0;
            m_paddle->setDx(dx);
            break;

        case Qt::Key_D:
            dx = 0;
            m_paddle->setDx(dx);
            break;
    }
}

void Breakout::keyPressEvent(QKeyEvent *e) {

    int dx = 0;

    switch (e->key()) {
    case Qt::Key_A:

        dx = -1;
        m_paddle->setDx(dx);

        break;

    case Qt::Key_D:

        dx = 1;
        m_paddle->setDx(dx);
        break;

    case Qt::Key_P:

        pauseGame();
        break;

    case Qt::Key_Space:
        if(!m_gameStarted)
        startGame();
        break;

    case Qt::Key_Backspace:
        exitGame();
        break;

    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::startGame() {

  if (!m_gameStarted) {
    m_ball->resetState();
    m_paddle->resetState();

    for (int i=0; i<N_OF_BRICKS; i++) {
      m_bricks[i]->setDestroyed(false);
    }

    m_gameOver = false;
    m_gameWon = false;
    m_gameStarted = true;
    m_timerId = startTimer(DELAY);
  }
}

void Breakout::pauseGame() {

  if (m_paused) {

    m_timerId = startTimer(DELAY);
    m_paused = false;
  } else {

    m_paused = true;
    killTimer(m_timerId);
  }
}

void Breakout::stopGame() {

  killTimer(m_timerId);
  m_gameOver = true;
  m_gameStarted = false;
}

void Breakout::victory() {

  killTimer(m_timerId);
  m_gameWon = true;
  m_gameStarted = false;
}

void Breakout::checkCollision() {

  if (m_ball->getRect().bottom() > BOTTOM_EDGE) {
    stopGame();
  }

  for (int i=0, j=0; i<N_OF_BRICKS; i++) {

    if (m_bricks[i]->isDestroyed()) {
      j++;
    }

    if (j == N_OF_BRICKS) {
      victory();
    }
  }

  if ((m_ball->getRect()).intersects(m_paddle->getRect())) {

    int paddleLPos = m_paddle->getRect().left();
    int ballLPos = m_ball->getRect().left();

    int first = paddleLPos + 8;
    int second = paddleLPos + 16;
    int third = paddleLPos + 24;
    int fourth = paddleLPos + 32;

    if (ballLPos < first) {
      m_ball->setXDir(-1);
      m_ball->setYDir(-1);
    }

    if (ballLPos >= first && ballLPos < second) {
      m_ball->setXDir(-1);
      m_ball->setYDir(-1*m_ball->getYDir());
    }

    if (ballLPos >= second && ballLPos < third) {
       m_ball->setXDir(0);
       m_ball->setYDir(-1);
    }

    if (ballLPos >= third && ballLPos < fourth) {
       m_ball->setXDir(1);
       m_ball->setYDir(-1*m_ball->getYDir());
    }

    if (ballLPos > fourth) {
      m_ball->setXDir(1);
      m_ball->setYDir(-1);
    }
  }

  for (int i=0; i<N_OF_BRICKS; i++) {

    if ((m_ball->getRect()).intersects(m_bricks[i]->getRect())) {

      int ballLeft = m_ball->getRect().left();
      int ballHeight = m_ball->getRect().height();
      int ballWidth = m_ball->getRect().width();
      int ballTop = m_ball->getRect().top();

      QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
      QPoint pointLeft(ballLeft - 1, ballTop);
      QPoint pointTop(ballLeft, ballTop -1);
      QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

      if (!m_bricks[i]->isDestroyed()) {
        if(m_bricks[i]->getRect().contains(pointRight)) {
           m_ball->setXDir(-1);
        }

        else if(m_bricks[i]->getRect().contains(pointLeft)) {
           m_ball->setXDir(1);
        }

        if(m_bricks[i]->getRect().contains(pointTop)) {
           m_ball->setYDir(1);
        }

        else if(m_bricks[i]->getRect().contains(pointBottom)) {
           m_ball->setYDir(-1);
        }

        m_bricks[i]->setDestroyed(true);
      }
    }
  }
}

void Breakout::createButtons()
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
    m_exitButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_exitButton->setDefault(false);
    m_exitButton->setAutoDefault(false);
    m_exitButton->setFocusPolicy(Qt::NoFocus);
    m_exitButton->hide();

    connect(m_againButton, SIGNAL(clicked(bool)), this, SLOT(againGame()));
    connect(m_exitButton, SIGNAL(clicked(bool)), this, SLOT(exitGame()));
}

void Breakout::exitGame()
{
    stopGame();
    emit exitClicked();

}

void Breakout::againGame()
{
    initGame();
    startGame();

}

void Breakout::initGame()
{
    m_x = 0;
    m_gameOver = false;
    m_gameWon = false;
    m_paused = false;
    m_gameStarted = false;
    m_againButton->hide();
    m_exitButton->hide();
}

void Breakout::setGame()
{
    initGame();
    m_ball->resetState();
    m_paddle->resetState();
    for (int i=0; i<N_OF_BRICKS; i++) {
      m_bricks[i]->setDestroyed(false);
    }
}
