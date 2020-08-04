QT       += core gui websockets

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
    FoolGameApplicationWindow/ApplicationWindow.cpp \
    FoolGameApplicationWindow/Objects/ServerConnector/ServerConnector.cpp \
    FoolGameApplicationWindow/Objects/UsersInformation/GameUserInformation/GameUserInformation.cpp \
    FoolGameApplicationWindow/Objects/UsersInformation/ThisUserFullInformation/ThisUserFullInformation.cpp \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatScene/ChatScene.cpp \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatScene/ChatWidget/ChatWidget.cpp \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatScene/ChatWidget/ChatWindow/ChatWindow.cpp \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatView/ChatView.cpp \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/CustomTabWidget/CustomTabWidget.cpp \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/StatusBar/InfoPanel/InfoPanel.cpp \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/StatusBar/StatusBar.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/BattleArea/BattleAreaWidget.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/BattleArea/BattlePair/BattlePairWidget.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/Card/Card.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/GameTableWidget.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/HandUp/HandUpWidget.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/PlayersDecks/OtherPlayerDeck/OtherPlayerDeck.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/PlayersDecks/SharedParentForPlayersDeck/SharedParentForPlayersDeck.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/PlayersDecks/ThisPlayerDeck/ThisPlayerDeck.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/StartDeck/StartDeckWidget.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/LoadingWindow/LoadingWindow.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/GameSelectionWindow/GameSelectionWindow.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/MenuWindow.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/OptionsWindow/GameSettingObject/GameSettingObject.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/OptionsWindow/OptionsWindow.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/PaymentWindow/PaymentWindow.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/RegistrationSystem/LogInWindow/LogInWindow.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/RegistrationSystem/RegistrationSystem.cpp \
    FoolGameApplicationWindow/Widgets/StatesWidgets/RegistrationSystem/RegistrationWindow/RegistrationWindow.cpp \
    main.cpp

HEADERS += \ \
    FoolGameApplicationWindow/ApplicationWindow.h \
    FoolGameApplicationWindow/Files/ChatCanals.h \
    FoolGameApplicationWindow/Files/SettingsStruct.h \
    FoolGameApplicationWindow/Files/TypesAliases.h \
    FoolGameApplicationWindow/Objects/ServerConnector/ServerConnector.h \
    FoolGameApplicationWindow/Objects/UsersInformation/GameUserInformation/GameUserInformation.h \
    FoolGameApplicationWindow/Objects/UsersInformation/ThisUserFullInformation/ThisUserFullInformation.h \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatScene/ChatScene.h \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatScene/ChatWidget/ChatWidget.h \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatScene/ChatWidget/ChatWindow/ChatWindow.h \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatView/ChatView.h \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/CustomTabWidget/CustomTabWidget.h \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/StatusBar/InfoPanel/InfoPanel.h \
    FoolGameApplicationWindow/Widgets/PermanentWidgets/StatusBar/StatusBar.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/BattleArea/BattleAreaWidget.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/BattleArea/BattlePair/BattlePairWidget.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/Card/Card.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/GameTableWidget.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/HandUp/HandUpWidget.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/PlayersDecks/OtherPlayerDeck/OtherPlayerDeck.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/PlayersDecks/SharedParentForPlayersDeck/SharedParentForPlayersDeck.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/PlayersDecks/ThisPlayerDeck/ThisPlayerDeck.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/StartDeck/StartDeckWidget.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/LoadingWindow/LoadingWindow.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/GameSelectionWindow/GameSelectionWindow.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/MenuWindow.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/OptionsWindow/GameSettingObject/GameSettingObject.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/OptionsWindow/OptionsWindow.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/PaymentWindow/PaymentWindow.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/RegistrationSystem/LogInWindow/LogInWindow.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/RegistrationSystem/RegistrationSystem.h \
    FoolGameApplicationWindow/Widgets/StatesWidgets/RegistrationSystem/RegistrationWindow/RegistrationWindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
