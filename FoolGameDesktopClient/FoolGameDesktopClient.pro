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
    ApplicationGUIPart/MainApplicationWindow/ApplicationWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/DefaultWindow/DefaultWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/OptionsWindow/OptionsWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/PaymentWindow/PaymentWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/RegistrationWindow/RegistrationWindow.cpp \
    ConnectWithServerPart/ApplicationEthernetController.cpp \
    InstanceGUIPart/GameTable/BattleArea/BattleAreaWidget.cpp \
    InstanceGUIPart/GameTable/BattlePair/BattlePairWidget.cpp \
    InstanceGUIPart/GameTable/Card/Card.cpp \
    InstanceGUIPart/GameTable/GameTableWidget.cpp \
    InstanceGUIPart/GameTable/HandUp/HandUpWidget.cpp \
    InstanceGUIPart/GameTable/OtherPlayerDeck/OtherPlayerDeckWidget.cpp \
    InstanceGUIPart/GameTable/SharedParentForPlayersDeck/SharedParentForPlayersDeck.cpp \
    InstanceGUIPart/GameTable/StartDeck/StartDeckWidget.cpp \
    InstanceGUIPart/GameTable/ThisPlayerDeck/ThisPlayerDeckWidget.cpp \
    main.cpp

HEADERS += \
    ApplicationGUIPart/MainApplicationWindow/ApplicationWindow.h \
    ApplicationGUIPart/MainApplicationWindow/DefaultWindow/DefaultWindow.h \
    ApplicationGUIPart/MainApplicationWindow/OptionsWindow/OptionsWindow.h \
    ApplicationGUIPart/MainApplicationWindow/PaymentWindow/PaymentWindow.h \
    ApplicationGUIPart/MainApplicationWindow/RegistrationWindow/RegistrationWindow.h \
    ConnectWithServerPart/ApplicationEthernetController.h \
    InstanceGUIPart/GameTable/BattleArea/BattleAreaWidget.h \
    InstanceGUIPart/GameTable/BattlePair/BattlePairWidget.h \
    InstanceGUIPart/GameTable/Card/Card.h \
    InstanceGUIPart/GameTable/Card/SharedOptions.h \
    InstanceGUIPart/GameTable/GameTableWidget.h \
    InstanceGUIPart/GameTable/HandUp/HandUpWidget.h \
    InstanceGUIPart/GameTable/OtherPlayerDeck/OtherPlayerDeckWidget.h \
    InstanceGUIPart/GameTable/SharedParentForPlayersDeck/SharedParentForPlayersDeck.h \
    InstanceGUIPart/GameTable/StartDeck/StartDeckWidget.h \
    InstanceGUIPart/GameTable/ThisPlayerDeck/ThisPlayerDeckWidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
