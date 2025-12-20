
TEMPLATE = app
QT += core widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dungeonbuilder.cpp \
    Enemy.cpp \
    Game.cpp \
    Monster.cpp \
    Player.cpp \
    Room.cpp \
    Savemanager.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Dungeonbuilder.h \
    Enemy.h \
    Game.h \
    Monster.h \
    Player.h \
    Room.h \
    Savemanager.h \
    Utils.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
