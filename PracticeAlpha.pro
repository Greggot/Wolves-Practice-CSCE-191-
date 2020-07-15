QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS += -LC:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:/SFML/include
DEPENDPATH += C:/SFML/include

SOURCES += \
    Engine.cpp \
    Figure.cpp \
    Point.cpp \
    Polygone.cpp \
    cilindrparametr.cpp \
    cubparametr.cpp \
    konusparametr.cpp \
    main.cpp \
    mainwindow.cpp \
    parallelepipedparametr.cpp \
    piramidaparametr.cpp \
    prizmparametr.cpp \
    sharparametr.cpp \
    upravlenie.cpp

HEADERS += \
    cilindrparametr.h \
    cubparametr.h \
    konusparametr.h \
    mainwindow.h \
    parallelepipedparametr.h \
    piramidaparametr.h \
    prizmparametr.h \
    sharparametr.h \
    upravlenie.h

FORMS += \
    cilindrparametr.ui \
    cubparametr.ui \
    konusparametr.ui \
    mainwindow.ui \
    parallelepipeparametr.ui \
    piramidaparametr.ui \
    prizmparametr.ui \
    sharparametr.ui \
    upravlenie.ui



TRANSLATIONS += \
    PracticeAlpha_ru_RU.ts



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
