#include "snake/snake.h"
#include "breakout/breakout.h"
#include "globalsettings.h"
#include "game.h"
#include "tictactoe/tictactoewindow.h"
#include "theme.h"
#include "gamemenu.h"
#include <QApplication>
#include <QTranslator>
#include <QPair>

QTranslator *qTranslator;

QPair<int, QTranslator*> language;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qTranslator = new QTranslator();
    language.first = 0;
    language.second = new QTranslator();
    a.installTranslator(qTranslator);
    a.installTranslator(language.second);
    Game w;
    w.show();

    return a.exec();
}
