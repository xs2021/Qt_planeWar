#-------------------------------------------------
#
# Project created by QtCreator 2021-05-05T18:55:22
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = planWar
TEMPLATE = app


SOURCES += main.cpp\
        mainscene.cpp \
    map.cpp \
    heroplane.cpp \
    bullet.cpp \
    enemyplane.cpp \
    bomb.cpp

HEADERS  += mainscene.h \
    config.h \
    map.h \
    heroplane.h \
    bullet.h \
    enemyplane.h \
    bomb.h
