#-------------------------------------------------
#
# Project created by QtCreator 2022-03-09T17:06:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GluttonousSnake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    food.cpp \
    gamecontroller.cpp \
    snake.cpp

HEADERS  += mainwindow.h \
    constants.h \
    food.h \
    gamecontroller.h \
    snake.h
