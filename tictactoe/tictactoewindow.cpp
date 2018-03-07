#include "tictactoe/tictactoewindow.h"
#include "ui_tictactoe.h"
#include "configurationdialog.h"
#include "globalsettings.h"
#include <QVBoxLayout>
#include <QMessageBox>

TictactoeWindow::TictactoeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(ui->player1);
    vlayout->addWidget(ui->gameBoard);
    vlayout->addWidget(ui->player2);

    setStyleSheet("QMessageBox{color: black;}");

    mainWidget->setLayout(vlayout);
    resize(WIDTH, HEIGHT);
    setCentralWidget(mainWidget);

    connect(ui->actionNewGame, SIGNAL(triggered(bool)), this, SLOT(startNewGame()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(goBack()));
    connect(ui->gameBoard, SIGNAL(currentPlayerChanged(TicTacToe::Player)),
    this, SLOT(updateNameLabels()));
    connect(ui->gameBoard, SIGNAL(gameOver(TicTacToe::Player)), this, SLOT(handleGameOver(TicTacToe::Player)));
    ui->gameBoard->setEnabled(false);
}

TictactoeWindow::~TictactoeWindow()
{
    delete ui;
}

void TictactoeWindow::startNewGame()
{
    ConfigurationDialog dlg(this);
    if(dlg.exec() == QDialog::Rejected)
    {

        return;
    }

    ui->player1->setText(dlg.player1Name());
    ui->player2->setText(dlg.player2Name());
    ui->gameBoard->initNewGame();
    ui->gameBoard->setEnabled(true);

}

void TictactoeWindow::updateNameLabels() {
    QFont f = ui->player1->font();
    f.setBold(ui->gameBoard->currentPlayer() ==
    TicTacToe::Player1);
    ui->player1->setFont(f);
    f.setBold(ui->gameBoard->currentPlayer() ==
    TicTacToe::Player2);
    ui->player2->setFont(f);
}

void TictactoeWindow::handleGameOver(TicTacToe::Player winner)
{
    ui->gameBoard->setEnabled(false);
    QString message;
    if(winner == TicTacToe::Draw)
    {
        message = "Game ended with a draw.";
    }
    else
    {
        message = QString("%1 wins").arg(winner == TicTacToe::Player1 ? ui->player1->text() : ui->player2->text());
    }
    QMessageBox::information(this, "Info", message);
}

void TictactoeWindow::goBack()
{
    emit backtomenuClicked();
}
