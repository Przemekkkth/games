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
            m_board.append(button);

            mapper->setMapping(button, m_board.count() - 1);
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
        m_board.at(i)->setText(" ");
    }
}

void TicTacToe::handleButtonClicked(int index)
{

    if(index < 0 || index >= m_board.size() )
    {
        return;
    }
    QPushButton *button = m_board.at(index);
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
    if( (m_board.at(0)->text() == "X") && (m_board.at(1)->text() == "X") && ((m_board.at(2)->text() == "X")) )
    {
        return true;
    }
    if( (m_board.at(3)->text() == "X") && (m_board.at(4)->text() == "X") && ((m_board.at(5)->text() == "X")) )
    {
        return true;
    }
    if( (m_board.at(6)->text() == "X") && (m_board.at(7)->text() == "X") && ((m_board.at(8)->text() == "X")) )
    {
        return true;
    }
    if( (m_board.at(0)->text() == "X") && (m_board.at(3)->text() == "X") && ((m_board.at(6)->text() == "X")) )
    {
        return true;
    }
    if( (m_board.at(1)->text() == "X") && (m_board.at(4)->text() == "X") && ((m_board.at(7)->text() == "X")) )
    {
        return true;
    }
    if( (m_board.at(2)->text() == "X") && (m_board.at(5)->text() == "X") && ((m_board.at(8)->text() == "X")) )
    {
        return true;
    }
    if( (m_board.at(0)->text() == "X") && (m_board.at(4)->text() == "X") && ((m_board.at(8)->text() == "X")) )
    {
        return true;
    }
    if( (m_board.at(2)->text() == "X") && (m_board.at(4)->text() == "X") && ((m_board.at(6)->text() == "X")) )
    {
        return true;
    }
    return false;
}

bool TicTacToe::checkO()
{
    if( (m_board.at(0)->text() == "O") && (m_board.at(1)->text() == "O") && ((m_board.at(2)->text() == "O")) )
    {
        return true;
    }
    if( (m_board.at(3)->text() == "O") && (m_board.at(4)->text() == "O") && ((m_board.at(5)->text() == "O")) )
    {
        return true;
    }
    if( (m_board.at(6)->text() == "O") && (m_board.at(7)->text() == "O") && ((m_board.at(8)->text() == "O")) )
    {
        return true;
    }
    if( (m_board.at(0)->text() == "O") && (m_board.at(3)->text() == "O") && ((m_board.at(6)->text() == "O")) )
    {
        return true;
    }
    if( (m_board.at(1)->text() == "O") && (m_board.at(4)->text() == "O") && ((m_board.at(7)->text() == "O")) )
    {
        return true;
    }
    if( (m_board.at(2)->text() == "O") && (m_board.at(5)->text() == "O") && ((m_board.at(8)->text() == "O")) )
    {
        return true;
    }
    if( (m_board.at(0)->text() == "O") && (m_board.at(4)->text() == "O") && ((m_board.at(8)->text() == "O")) )
    {
        return true;
    }
    if( (m_board.at(2)->text() == "O") && (m_board.at(4)->text() == "O") && ((m_board.at(6)->text() == "O")) )
    {
        return true;
    }

    return false;
}

bool TicTacToe::checkDraw()
{
    if(

            ((m_board.at(0)->text() == "O") || (m_board.at(0)->text() == "X"))
            &&
            ((m_board.at(1)->text() == "O") || (m_board.at(1)->text() == "X"))
            &&
            ((m_board.at(2)->text() == "O") || (m_board.at(2)->text() == "X"))
            &&
            ((m_board.at(3)->text() == "O") || (m_board.at(3)->text() == "X"))
            &&
            ((m_board.at(4)->text() == "O") || (m_board.at(4)->text() == "X"))
            &&
            ((m_board.at(5)->text() == "O") || (m_board.at(5)->text() == "X"))
            &&
            ((m_board.at(6)->text() == "O") || (m_board.at(6)->text() == "X"))
            &&
            ((m_board.at(7)->text() == "O") || (m_board.at(7)->text() == "X"))
            &&
            ((m_board.at(8)->text() == "O") || (m_board.at(8)->text() == "X"))
      )
    {

        return true;
    }

       return false;
}
