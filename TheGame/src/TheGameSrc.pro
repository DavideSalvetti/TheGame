QT += qml quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        command.cpp \
        entity/archer.cpp \
        entity/castle.cpp \
        entity/character.cpp \
        entity/characterfactory.cpp \
        entity/dynamicentity.cpp \
        entity/entity.cpp \
        entity/knight.cpp \
        entity/magician.cpp \
        entity/ninja.cpp \
        entity/staticentity.cpp \
        entity/swordsman.cpp \
        game.cpp \
        main.cpp \
        map/map.cpp \
        map/tile.cpp

RESOURCES += qml.qrc \
    assets.qrc \
    components.qrc \
    image.qrc \
    panels.qrc

RC_ICONS = C:\Users\Davide\Desktop\TheGame\TheGame\TheGame\src\img\crown.ico
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    src/TheGameSrc.pro

HEADERS += \
    command.h \
    entity/archer.h \
    entity/castle.h \
    entity/character.h \
    entity/characterfactory.h \
    entity/dynamicentity.h \
    entity/entity.h \
    entity/knight.h \
    entity/magician.h \
    entity/ninja.h \
    entity/staticentity.h \
    entity/swordsman.h \
    game.h \
    map/map.h \
    map/tile.h
