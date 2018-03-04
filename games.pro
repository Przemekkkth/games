#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T20:16:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake1
TEMPLATE = app

TRANSLATIONS += en_EN.ts \
                rus_RUS.ts \
                ger_GER.ts\
                pl_PL.ts


SOURCES += main.cpp\
    theme.cpp \
    game.cpp \
    gamemenu.cpp \
    breakout/ball.cpp \
    breakout/breakout.cpp \
    breakout/brick.cpp \
    breakout/paddle.cpp \
    snake/snake.cpp \
    tictactoe/configurationdialog.cpp \
    tictactoe/tictactoe.cpp \
    tictactoe/tictactoewindow.cpp \
    options.cpp

HEADERS  += \
    theme.h \
    game.h \
    globalsettings.h \
    gamemenu.h \
    breakout/ball.h \
    breakout/breakout.h \
    breakout/brick.h \
    breakout/paddle.h \
    snake/snake.h \
    tictactoe/configurationdialog.h \
    tictactoe/tictactoe.h \
    tictactoe/tictactoewindow.h \
    options.h

FORMS += \
    configurationdialog.ui \
    tictactoe.ui \
    options.ui

RESOURCES += \
    images.qrc