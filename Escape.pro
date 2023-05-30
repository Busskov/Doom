QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    realizations/controller.cpp \
    realizations/draw/drawGun.cpp \
    realizations/draw/drawMonsters.cpp \
    realizations/draw/drawScore.cpp \
    realizations/draw/drawWalls.cpp \
    realizations/gun.cpp \
    realizations/main.cpp \
    realizations/map.cpp \
    realizations/model.cpp \
    realizations/monster.cpp \
    realizations/monsters.cpp \
    realizations/player.cpp \
    realizations/shoot.cpp \
    realizations/view.cpp

HEADERS += \
    classes/controller.h \
    classes/map.h \
    classes/model.h \
    classes/monster.h \
    classes/monsters.h \
    classes/player.h \
    classes/gun.h \
    classes/view.h

FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
