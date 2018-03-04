#include "tictactoe.h"
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <QMessageBox>

TicTacToe::TicTacToe(QWidget *parent) : QWidget(parent)
{
    setupBoard();
    initNewGame();
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void TicTacToe::setupBoard()
{
    QGridLayout *gridLayout = new QGridLayout;
    QSignalMapper *mapper = new QSignalMapper(this);
    for(int row = 0; row < 3; ++row)
    {
        for(int column = 0; column < 3; ++column)
        {
            QPushButton *button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Expanding,
                                  QSizePolicy::Expanding);
            button->setText(" ");
            gridLayout->addWidget(button, row, column);
            board.append(button);

            mapper->setMapping(button, board.count() - 1);
            connect(button, SIGNAL(clicked(bool)), mapper, SLOT(map()));
        }
    }
    setLayout(gridLayout);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleButtonClicked(int)));
}


void TicTacToe::initNewGame()
{
    for(int i = 0; i < 9; ++i)
    {
        board.at(i)->setText(" ");
    }
}

void TicTacToe::handleButtonClicked(int index)
{

    if(index < 0 || index >= board.size() )
    {
        return;
    }
    QPushButton *button = board.at(index);
    if(button->text() != " ")
    {
        return;
    }

    button->setText(currentPlayer() == Player1 ? "X" : "O");

    Player winner = checkWinCondition(index/3, index % 3);


    if(winner == Invalid)
    {
        setCurrentPlayer(currentPlayer() == Player1 ? Player2 : Player1);
        return;
    }
    else
    {
        emit gameOver(winner);
    }
}

TicTacToe::Player TicTacToe::checkWinCondition(int r, int c)
{
    if(checkO())
    {
        return Player1;
    }
    if(checkX())
    {
        return Player2;
    }
    if(checkDraw())
    {
        return Draw;
    }


    return Invalid;
}

bool TicTacToe::checkX()
{
    if( (board.at(0)->text() == "X") && (board.at(1)->text() == "X") && ((board.at(2)->text() == "X")) )
    {
        return true;
    }
    if( (board.at(3)->text() == "X") && (board.at(4)->text() == "X") && ((board.at(5)->text() == "X")) )
    {
        return true;
    }
    if( (board.at(6)->text() == "X") && (board.at(7)->text() == "X") && ((board.at(8)->text() == "X")) )
    {
        return true;
    }
    if( (board.at(0)->text() == "X") && (board.at(3)->text() == "X") && ((board.at(6)->text() == "X")) )
    {
        return true;
    }
    if( (board.at(1)->text() == "X") && (board.at(4)->text() == "X") && ((board.at(7)->text() == "X")) )
    {
        return true;
    }
    if( (board.at(2)->text() == "X") && (board.at(5)->text() == "X") && ((board.at(8)->text() == "X")) )
    {
        return true;
    }
    if( (board.at(0)->text() == "X") && (board.at(4)->text() == "X") && ((board.at(8)->text() == "X")) )
    {
        return true;
    }
    if( (board.at(2)->text() == "X") && (board.at(4)->text() == "X") && ((board.at(6)->text() == "X")) )
    {
        return true;
    }
    return false;
}

bool TicTacToe::checkO()
{
    if( (board.at(0)->text() == "O") && (board.at(1)->text() == "O") && ((board.at(2)->text() == "O")) )
    {
        return true;
    }
    if( (board.at(3)->text() == "O") && (board.at(4)->text() == "O") && ((board.at(5)->text() == "O")) )
    {
        return true;
    }
    if( (board.at(6)->text() == "O") && (board.at(7)->text() == "O") && ((board.at(8)->text() == "O")) )
    {
        return true;
    }
    if( (board.at(0)->text() == "O") && (board.at(3)->text() == "O") && ((board.at(6)->text() == "O")) )
    {
        return true;
    }
    if( (board.at(1)->text() == "O") && (board.at(4)->text() == "O") && ((board.at(7)->text() == "O")) )
    {
        return true;
    }
    if( (board.at(2)->text() == "O") && (board.at(5)->text() == "O") && ((board.at(8)->text() == "O")) )
    {
        return true;
    }
    if( (board.at(0)->text() == "O") && (board.at(4)->text() == "O") && ((board.at(8)->text() == "O")) )
    {
        return true;
    }
    if( (board.at(2)->text() == "O") && (board.at(4)->text() == "O") && ((board.at(6)->text() == "O")) )
    {
        return true;
    }

    return false;
}

bool TicTacToe::checkDraw()
{
    if(

            ((board.at(0)->text() == "O") || (board.at(0)->text() == "X"))
            &&
            ((board.at(1)->text() == "O") || (board.at(1)->text() == "X"))
            &&
            ((board.at(2)->text() == "O") || (board.at(2)->text() == "X"))
            &&
            ((board.at(3)->text() == "O") || (board.at(3)->text() == "X"))
            &&
            ((board.at(4)->text() == "O") || (board.at(4)->text() == "X"))
            &&
            ((board.at(5)->text() == "O") || (board.at(5)->text() == "X"))
            &&
            ((board.at(6)->text() == "O") || (board.at(6)->text() == "X"))
            &&
            ((board.at(7)->text() == "O") || (board.at(7)->text() == "X"))
            &&
            ((board.at(8)->text() == "O") || (board.at(8)->text() == "X"))
      )
    {

        return true;
    }

       return false;
}
