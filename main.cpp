#include "snake/snake.h"
#include "breakout/breakout.h"
#include "globalsettings.h"
#include "game.h"
#include "tictactoe/tictactoewindow.h"
#include "theme.h"
#include "gamemenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game w;
    w.show();

    return a.exec();
}
