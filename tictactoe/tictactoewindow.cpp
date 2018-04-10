#include "tictactoewindow.h"
#include "configurationdialog.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QLabel>
#include <QWidget>
#include <QMenu>
#include <QAction>


TictactoeWindow::TictactoeWindow(QWidget *parent) :
    QMainWindow(parent)
{
	createWidgets();
	createLayouts();
	translateUi();
    createStyleSheets();
    createConnections();
    m_tictactoeWidget->setEnabled(false);
}

void TictactoeWindow::createWidgets()
{
	m_player1Label = new QLabel;
	m_player2Label = new QLabel;
    m_mainWidget = new QWidget(this);

    m_tictactoeWidget = new TicTacToe;
    m_newMenu = new QMenu();
    m_startAction = new QAction(0);
    m_quitAction = new QAction(0);
}
	
void TictactoeWindow::createLayouts()
{
    m_newMenu = menuBar()->addMenu("");
    m_newMenu->addAction(m_startAction);
    m_newMenu->addAction(m_quitAction);


    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(m_player1Label,0,Qt::AlignTop);
    vlayout->addWidget(m_tictactoeWidget);
    vlayout->addWidget(m_player2Label,0,Qt::AlignBottom);



    m_mainWidget->setLayout(vlayout);
    resize(333, 333);
    setCentralWidget(m_mainWidget);
}

void TictactoeWindow::translateUi()
{
    m_newMenu->setTitle(tr("New"));
    m_startAction->setText(tr("Start"));
    m_quitAction->setText(tr("Quit"));
    m_player1Label->setText(tr("player1"));
    m_player2Label->setText(tr("player2"));
}

void TictactoeWindow::createStyleSheets()
{
    setStyleSheet("QMessageBox{color: black;}");
    m_mainWidget->setStyleSheet("QMessageBox{color: black;}");
}

TictactoeWindow::~TictactoeWindow()
{
    
}

void TictactoeWindow::startNewGame()
{
    ConfigurationDialog dlg(this);
    if(dlg.exec() == QDialog::Rejected)
    {

        return;
    }

    m_player1Label->setText(dlg.player1Name());
    m_player2Label->setText(dlg.player2Name());
    m_tictactoeWidget->initNewGame();
    m_tictactoeWidget->setEnabled(true);
}

void TictactoeWindow::updateNameLabels() {
    QFont f = m_player1Label->font();
    f.setBold(m_tictactoeWidget->currentPlayer() ==
    TicTacToe::Player1);
    m_player1Label->setFont(f);
    f.setBold(m_tictactoeWidget->currentPlayer() ==
    TicTacToe::Player2);
    m_player2Label->setFont(f);
}

void TictactoeWindow::handleGameOver(TicTacToe::Player winner)
{
    m_tictactoeWidget->setEnabled(false);
    QString message;
    if(winner == TicTacToe::Draw)
    {
        message = "Game ended with a draw.";
    }
    else
    {
        message = QString("%1 wins").arg(winner == TicTacToe::Player1 ? m_player1Label->text() : m_player2Label->text());
    }
    QMessageBox::information(this, "Info", message);
}

void TictactoeWindow::goBack()
{
    emit backtomenuClicked();
}
void TictactoeWindow::createConnections()
{
    connect(m_startAction, SIGNAL(triggered(bool)), this, SLOT(startNewGame()));
    connect(m_quitAction, SIGNAL(triggered(bool)), this, SLOT(goBack()));
    connect(m_tictactoeWidget, SIGNAL(currentPlayerChanged(TicTacToe::Player)),
    this, SLOT(updateNameLabels()));
    connect(m_tictactoeWidget, SIGNAL(gameOver(TicTacToe::Player)), this, SLOT(handleGameOver(TicTacToe::Player)));

}
