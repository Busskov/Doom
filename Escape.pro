QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller.cpp \
    drawGun.cpp \
    drawMonsters.cpp \
    drawScore.cpp \
    drawWalls.cpp \
    gun.cpp \
    main.cpp \
    map.cpp \
    model.cpp \
    monster.cpp \
    monsters.cpp \
    player.cpp \
    shoot.cpp \
    view.cpp

HEADERS += \
    controller.h \
    map.h \
    model.h \
    monster.h \
    monsters.h \
    player.h \
    gun.h \
    view.h

FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
