#include "gamemenu.h"
#include <QPushButton>
#include <QVBoxLayout>
GameMenu::GameMenu(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QWidget{background-color: black;}"
                  "QPushButton{background-color: #13100a; border-style: solid;  border-width: 1px; border-radius: 10px; color: white; font-size: 20px; font-family: \'Arial\'; font-weight: 500px;}"
                  "QPushButton:hover{background-color: #24211b;}");



    m_TicTacToeButton = new QPushButton();
    m_TicTacToeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_TicTacToeButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_TicTacToeButton->setDefault(false);
    m_TicTacToeButton->setAutoDefault(false);


    m_ArcanoidButton = new QPushButton();
    m_ArcanoidButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_ArcanoidButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ArcanoidButton->setDefault(false);
    m_ArcanoidButton->setAutoDefault(false);

    m_SnakeButton = new QPushButton();
    m_SnakeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_SnakeButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_SnakeButton->setDefault(false);
    m_SnakeButton->setAutoDefault(false);

    m_BackToMenuButton = new QPushButton();
    m_BackToMenuButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_BackToMenuButton->setCursor(QCursor(Qt::PointingHandCursor));

    translateUi();
    createConnections();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_TicTacToeButton);
    layout->addWidget(m_ArcanoidButton);
    layout->addWidget(m_SnakeButton);
    layout->addWidget(m_BackToMenuButton);

    setLayout(layout);
}



void GameMenu::clickTicTacToe()
{
    emit tictactoeClicked();
}

void GameMenu::clickArcanoid()
{
    emit arcanoidClicked();
}

void GameMenu::clickSnake()
{
    emit snakeClicked();
}

void GameMenu::clickBackToMenu()
{
    emit backtomenuClicked();
}

void GameMenu::createConnections()
{
    connect(m_TicTacToeButton, SIGNAL(clicked(bool)), this, SLOT(clickTicTacToe()));
    connect(m_ArcanoidButton, SIGNAL(clicked(bool)), this, SLOT(clickArcanoid()));
    connect(m_SnakeButton, SIGNAL(clicked(bool)) , this, SLOT(clickSnake()));
    connect(m_BackToMenuButton, SIGNAL(clicked(bool)), this, SLOT(clickBackToMenu()));
}

void GameMenu::translateUi()
{
    m_TicTacToeButton->setText(tr("TicTacToe"));
    m_ArcanoidButton->setText(tr("Arcanoid"));
    m_SnakeButton->setText(tr("Snake"));
    m_BackToMenuButton->setText(tr("Back"));
}
