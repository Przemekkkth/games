#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>

class QPushButton;
class TicTacToe : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Player)
    Q_PROPERTY(Player currentPlayer READ currentPlayer WRITE setCurrentPlayer NOTIFY currentPlayerChanged)
public:
    void initNewGame();
    explicit TicTacToe(QWidget *parent = 0);
    enum Player {Invalid, Player1, Player2, Draw};
    Player m_currentPlayer;
    Player currentPlayer() const
    {
        return m_currentPlayer;
    }
    void setCurrentPlayer(Player p)
    {
        if(m_currentPlayer == p)
        {
            return;
        }
        m_currentPlayer = p;
        emit currentPlayerChanged(m_currentPlayer);
    }

signals:
    void currentPlayerChanged(TicTacToe::Player);
    void gameOver(TicTacToe::Player);
public slots:
    void handleButtonClicked(int);
private:
    QList<QPushButton*> board;
    void setupBoard();

    TicTacToe::Player checkWinCondition(int r, int c);
    bool checkX();
    bool checkO();
    bool checkDraw();
};

#endif // TICTACTOE_H
