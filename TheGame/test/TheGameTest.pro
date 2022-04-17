QT       += qml core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/command.cpp \
    ../src/entity/archer.cpp \
    ../src/entity/castle.cpp \
    ../src/entity/character.cpp \
    ../src/entity/characterfactory.cpp \
    ../src/entity/dynamicentity.cpp \
    ../src/entity/entity.cpp \
    ../src/entity/magician.cpp \
    ../src/entity/Swordsman.cpp \
    ../src/entity/staticentity.cpp \
    ../src/game.cpp \
    ../src/map/map.cpp \
    ../src/map/tile.cpp \
    main.cpp \
    testcharacter.cpp \
    testgame.cpp \
    testmap.cpp \
    testtile.cpp

HEADERS += \
    ../src/command.h \
    ../src/entity/CharacterFactoryIF.h \
    ../src/entity/archer.h \
    ../src/entity/castle.h \
    ../src/entity/character.h \
    ../src/entity/characterfactory.h \
    ../src/entity/dynamicentity.h \
    ../src/entity/entity.h \
    ../src/entity/magician.h \
    ../src/entity/Swordsman.h \
    ../src/entity/staticentity.h \
    ../src/game.h \
    ../src/map/map.h \
    ../src/map/tile.h \
    testcharacter.h \
    testgame.h \
    testmap.h \
    testtile.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
