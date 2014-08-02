#-------------------------------------------------
#
# Project created by QtCreator 2014-08-02T10:03:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = mini-game
TEMPLATE = app


SOURCES += \
    box2dengine.cpp \
    main.cpp \
    qworldview.cpp \
    Ship.cpp \
    PlayerShip.cpp

HEADERS  += \
    qworldview.h \
    box2dengine.h \
    MotionFilter.h \
    Ship.h \
    PlayerShip.h


FORMS    += 

CONFIG += mobility
MOBILITY = 

INCLUDEPATH += /home/dek/Box2D/v2.3.1/Box2D

linux-g++ | linux-g++-64 | linux-g++-32 {
    LIBS += -L/home/dek/Box2D/v2.3.1/build-Box2D-Desktop_Qt_5_3_GCC_64bit-Debug -lBox2D
}

android-g++ {
    LIBS += -L/home/dek/Box2D/v2.3.1/build-Box2D-Android_for_armeabi_v7a_GCC_4_8_Qt_5_3_1-Release -lBox2D

}
