#-------------------------------------------------
#
# Project created by QtCreator 2014-08-02T10:03:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sensors

QMAKE_CXXFLAGS += -std=c++11

TARGET = mini-game
TEMPLATE = app


SOURCES += \
    box2dengine.cpp \
    main.cpp \
    PlayerShip.cpp \
    EnemyShip.cpp \
    Cave.cpp \
    Diamond.cpp \
    PolygonItem.cpp \
    Item.cpp \
    World.cpp

HEADERS  += \
    box2dengine.h \
    MotionFilter.h \
    PlayerShip.h \
    EnemyShip.h \
    Cave.h \
    Diamond.h \
    MyContactListener.h \
    PolygonItem.h \
    Item.h \
    World.h


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

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
