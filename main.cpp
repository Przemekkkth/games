#include "snake/snake.h"
#include "breakout/breakout.h"
#include "globalsettings.h"
#include "game.h"
#include "tictactoe/tictactoewindow.h"
#include "theme.h"
#include "gamemenu.h"
#include <QApplication>
#include <QTranslator>

QTranslator *qTranslator;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qTranslator = new QTranslator();
    a.installTranslator(qTranslator);
    Game w;
    w.show();

    return a.exec();
}
