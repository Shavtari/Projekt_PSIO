TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt
CONFIG -= console

SOURCES += \
        enemy.cpp \
        enemy1.cpp \
        enemy2.cpp \
        enemyboss.cpp \
        game.cpp \
        main.cpp \
        player.cpp \
        projectile.cpp
        INCLUDEPATH += "D:/SFML/SFML-2.5.1/include"
                LIBS += -L"D:/SFML/SFML-2.5.1/lib"
                CONFIG(debug, debug|release){
                    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
                } else {
                    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
                }

HEADERS += \
    enemy.h \
    enemy1.h \
    enemy2.h \
    enemyboss.h \
    game.h \
    player.h \
    projectile.h
