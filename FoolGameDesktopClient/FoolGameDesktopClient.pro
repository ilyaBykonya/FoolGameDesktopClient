QT       += core gui network

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

SOURCES += \
    Card/Card.cpp \
    ConnectWithServerPart/ApplicationEthernetController.cpp \
    GUIpart/BattleArea/BattleAreaWidget.cpp \
    GUIpart/BattlePair/BattlePairWidget.cpp \
    GUIpart/GameTable/GameTableWidget.cpp \
    GUIpart/HandUp/HandUpWidget.cpp \
    GUIpart/OtherPlayerDeck/OtherPlayerDeckWidget.cpp \
    GUIpart/SharedParentForPlayersDeck/SharedParentForPlayersDeck.cpp \
    GUIpart/StartDeck/StartDeckWidget.cpp \
    GUIpart/ThisPlayerDeck/ThisPlayerDeckWidget.cpp \
    main.cpp

HEADERS += \
    Card/Card.h \
    Card/SharedOptions.h \
    ConnectWithServerPart/ApplicationEthernetController.h \
    GUIpart/BattleArea/BattleAreaWidget.h \
    GUIpart/BattlePair/BattlePairWidget.h \
    GUIpart/GameTable/GameTableWidget.h \
    GUIpart/HandUp/HandUpWidget.h \
    GUIpart/OtherPlayerDeck/OtherPlayerDeckWidget.h \
    GUIpart/SharedParentForPlayersDeck/SharedParentForPlayersDeck.h \
    GUIpart/StartDeck/StartDeckWidget.h \
    GUIpart/ThisPlayerDeck/ThisPlayerDeckWidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
