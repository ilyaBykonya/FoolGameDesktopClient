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
    ApplicationGUIPart/MainApplicationWindow/ApplicationWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/LoadingWindow/LoadingWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/CustomTabWidget/CustomTabWidget.cpp \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/GameSelectionWindow/GameSelectionWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/GameSelectionWindow/MinMaxWidget/MinMaxWidget.cpp \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/MenuWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/OptionsWindow/GameSettingObject/GameSettingObject.cpp \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/OptionsWindow/OptionsWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/PaymentWindow/PaymentWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/RegistrationSystem/LogInWindow/LogInWindow.cpp \
    ApplicationGUIPart/MainApplicationWindow/RegistrationSystem/RegistrationSystem.cpp \
    ApplicationGUIPart/MainApplicationWindow/RegistrationSystem/RegistrationWindow/RegistrationWindow.cpp \
    ChatWindow/ChatScene/ChatScene.cpp \
    ChatWindow/ChatScene/ChatWidget/ChatWidget.cpp \
    ChatWindow/ChatScene/ChatWidget/ChatWindow/ChatWindow.cpp \
    ChatWindow/ChatScene/ChatWidget/CustomTabWidget/CustomTabWidget.cpp \
    ChatWindow/ChatView/ChatView.cpp \
    ConnectWithServerPart/ApplicationEthernetController.cpp \
    InstanceGUIPart/GameTable/BattleArea/BattleAreaWidget.cpp \
    InstanceGUIPart/GameTable/BattleArea/BattlePair/BattlePairWidget.cpp \
    InstanceGUIPart/GameTable/Card/Card.cpp \
    InstanceGUIPart/GameTable/GameTableWidget.cpp \
    InstanceGUIPart/GameTable/HandUp/HandUpWidget.cpp \
    InstanceGUIPart/GameTable/Player/PlayerDecks/OtherPlayerDeck/OtherPlayerDeckWidget.cpp \
    InstanceGUIPart/GameTable/Player/PlayerDecks/SharedParentForPlayersDeck/SharedPlayersDeckParent.cpp \
    InstanceGUIPart/GameTable/Player/PlayerDecks/ThisPlayerDeck/ThisPlayerDeckWidget.cpp \
    InstanceGUIPart/GameTable/Player/ShowUserInfo/ShowUserInfoWidget.cpp \
    InstanceGUIPart/GameTable/StartDeck/StartDeckWidget.cpp \
    UserInformation/UserInformation.cpp \
    main.cpp

HEADERS += \ \
    ApplicationGUIPart/MainApplicationWindow/ApplicationWindow.h \
    ApplicationGUIPart/MainApplicationWindow/LoadingWindow/LoadingWindow.h \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/CustomTabWidget/CustomTabWidget.h \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/GameSelectionWindow/GameSelectionWindow.h \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/GameSelectionWindow/MinMaxWidget/MinMaxWidget.h \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/MenuWindow.h \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/OptionsWindow/GameSettingObject/GameSettingObject.h \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/OptionsWindow/GameSettingObject/SettingsStruct/SettingsStruct.h \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/OptionsWindow/OptionsWindow.h \
    ApplicationGUIPart/MainApplicationWindow/MenuWindow/PaymentWindow/PaymentWindow.h \
    ApplicationGUIPart/MainApplicationWindow/RegistrationSystem/LogInWindow/LogInWindow.h \
    ApplicationGUIPart/MainApplicationWindow/RegistrationSystem/RegistrationSystem.h \
    ApplicationGUIPart/MainApplicationWindow/RegistrationSystem/RegistrationWindow/RegistrationWindow.h \
    ChatWindow/ChatScene/ChatScene.h \
    ChatWindow/ChatScene/ChatWidget/CanalsList.h \
    ChatWindow/ChatScene/ChatWidget/ChatWidget.h \
    ChatWindow/ChatScene/ChatWidget/ChatWindow/ChatWindow.h \
    ChatWindow/ChatScene/ChatWidget/CustomTabWidget/CustomTabWidget.h \
    ChatWindow/ChatView/ChatView.h \
    ConnectWithServerPart/ApplicationEthernetController.h \
    InstanceGUIPart/GameTable/BattleArea/BattleAreaWidget.h \
    InstanceGUIPart/GameTable/BattleArea/BattlePair/BattlePairWidget.h \
    InstanceGUIPart/GameTable/Card/Card.h \
    InstanceGUIPart/GameTable/GameTableWidget.h \
    InstanceGUIPart/GameTable/HandUp/HandUpWidget.h \
    InstanceGUIPart/GameTable/Player/PlayerDecks/OtherPlayerDeck/OtherPlayerDeckWidget.h \
    InstanceGUIPart/GameTable/Player/PlayerDecks/SharedParentForPlayersDeck/SharedPlayersDeckParent.h \
    InstanceGUIPart/GameTable/Player/PlayerDecks/ThisPlayerDeck/ThisPlayerDeckWidget.h \
    InstanceGUIPart/GameTable/Player/ShowUserInfo/ShowUserInfoWidget.h \
    InstanceGUIPart/GameTable/StartDeck/StartDeckWidget.h \
    TypesAliases.h \
    UserInformation/UserInformation.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target