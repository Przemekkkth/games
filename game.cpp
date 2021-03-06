#include "game.h"
#include "theme.h"
#include "snake/snake.h"
#include "globalsettings.h"
#include "tictactoe/tictactoewindow.h"
#include "breakout/breakout.h"
#include "gamemenu.h"
#include "options/options.h"
#include <QStackedWidget>
#include <QLayout>
#include <QMessageBox>
#include <QPainter>

Game::Game(QWidget *parent)
    : QWidget(parent)
{

    createWidgets();
    createLayout();
    createConnections();
    createContainer();
    createStyleSheet();
    init();
}


void Game::createWidgets()
{
    m_mainContent = new QStackedWidget;
    m_theme = new Theme;
    m_snake = new Snake;
    m_tictactoe = new TictactoeWindow;
    m_breakout = new Breakout;
    m_gameMenu = new GameMenu;
    m_options = new Options;
}

void Game::createConnections()
{
    connect(m_theme, SIGNAL(startClicked()), this, SLOT(setGameMenuContent()));
    connect(m_theme, SIGNAL(optionsClicked()), this, SLOT(setOptionsContent()) );

    connect(m_gameMenu, SIGNAL(backtomenuClicked()), this, SLOT(setThemeContent()));
    connect(m_gameMenu, SIGNAL(arcanoidClicked()), this, SLOT(setBreakoutContent()));
    connect(m_gameMenu, SIGNAL(snakeClicked()), this, SLOT(setSnakeContent()));
    connect(m_gameMenu, SIGNAL(tictactoeClicked()), this, SLOT(setTicTacToeContent()));

    connect(m_snake, SIGNAL(exitClicked()), this, SLOT(setGameMenuContent()));

    connect(m_breakout, SIGNAL(exitClicked()), this, SLOT(setGameMenuContent()));

    connect(m_options, SIGNAL(backtomenuClicked()), this, SLOT(setThemeContent()));

    connect(m_tictactoe, SIGNAL(backtomenuClicked()), this, SLOT(setThemeContent()));
}

void Game::setGameMenuContent()
{
    m_mainContent->setCurrentIndex(1);
}

void Game::setBreakoutContent()
{
    m_mainContent->setCurrentIndex(2);
    m_breakout->setGame();
}

void Game::setSnakeContent()
{
    m_mainContent->setCurrentIndex(3);
    m_snake->setGame();
}

void Game::setTicTacToeContent()
{

    m_mainContent->setCurrentIndex(4);
}

void Game::setThemeContent()
{
    m_mainContent->setCurrentIndex(0);
}

void Game::paintEvent(QPaintEvent*)
{
    QPainter qp(this);
    qp.setBrush(QBrush(Qt::black));
    qp.drawRect(rect());
}

void Game::setOptionsContent()
{
    m_mainContent->setCurrentIndex(5);
}


void Game::createContainer()
{
    m_mainContent->addWidget(m_theme);

    m_mainContent->addWidget(m_gameMenu);

    m_mainContent->addWidget(m_breakout);

    m_mainContent->addWidget(m_snake);

    m_mainContent->addWidget(m_tictactoe);

    m_mainContent->addWidget(m_options);
}

void Game::createLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_mainContent);
    layout->setMargin(0);
    setLayout(layout);
}

void Game::createStyleSheet()
{
    m_mainContent->setStyleSheet("QLabel{color: red;}"
                                 "QMessageBox{color: black;}");
    resize(WIDTH, HEIGHT);
}

void Game::init()
{
    setWindowIcon(QIcon(":/images/icon"));
    setMaximumSize(QSize(300, 325));
    setMinimumSize(QSize(300, 325));
    setWindowTitle("Games");
}
