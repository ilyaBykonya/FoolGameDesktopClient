#pragma once
#include "FoolGameApplicationWindow/Objects/ServerConnector/ServerConnector.h"
#include "FoolGameApplicationWindow/Objects/UsersInformation/GameUserInformation/GameUserInformation.h"
#include "FoolGameApplicationWindow/Objects/UsersInformation/ThisUserFullInformation/ThisUserFullInformation.h"


#include "FoolGameApplicationWindow/Widgets/PermanentWidgets/StatusBar/StatusBar.h"
#include "FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatView/ChatView.h"
#include "FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatScene/ChatScene.h"

#include "FoolGameApplicationWindow/Widgets/StatesWidgets/RegistrationSystem/RegistrationSystem.h"
#include "FoolGameApplicationWindow/Widgets/StatesWidgets/MenuWindow/MenuWindow.h"
#include "FoolGameApplicationWindow/Widgets/StatesWidgets/LoadingWindow/LoadingWindow.h"
#include "FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/GameTableWidget.h"



#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>


class ApplicationWindow : public QWidget
{
    Q_OBJECT
public:
    enum UserState
    {
        UserNoSignIn = 0,
        UserInLobbi,
        UserWaitGame,
        UserInGame
    };
private:
    ServerConnector* m_ethernetController;
    ThisUserFullInformation* m_thisUserFullInfo;



    QVBoxLayout* m_layout;

    ChatScene* m_chatSceneObject;
    StatusBar* m_statusBar;

    RegistrationSystem* m_registrationMenu;
    MenuWindow* m_menuWindow;
    LoadingWindow* m_loadingWindow;
    GameTableWidget* m_instanceWindow;




    UserState m_userState;
public:
    explicit ApplicationWindow(const QString&, quint16, QWidget *parent = nullptr);

signals:
    void signalExitButtonWasClicked(bool);

public slots:
    void transitionFromRegistrationWindowToMenu(UserID, const QString&, Cash, Cash, quint32, quint32, const QPixmap&);
    void transitionFromMenuToRegistrationWindow();

    void transitionFromMenuToLoadingWindow();
    void transitionFromLoadingWindowToMenu();

    void transitionFromLoadingWindowToGameInstance(Card::Suit, Card::Dignity, UserID, QList<GameUserInformation*>, UserID, UserID, DeckSize);
    void transitionFromGameInstanceToMenu(QList<GameUserInformation*>);



    void slotUpdateUserInfo(const QString&, Cash, Cash, quint32, quint32);
    void slotMakeAlert(const QString&, const QString&);

private:
    void createChatScene();
    void destructChatScene();


    void createStatusBar(ThisUserFullInformation*);
    void destructStatusBar();

    void createUserFullInfo(UserID, const QString&, Cash, Cash, quint32, quint32, const QPixmap&);
    void destructUserFullInfo();





    void createReistrationWindow();
    void destructRegistrationWindow();

    void createMenuWindow();
    void destructMenuWindow();

    void createLoadingWindow();
    void destructLoadingWindow();

    void createGameInstanceWindow(Card::Suit trumpS, Card::Dignity trumpD, UserID thisID, QList<GameUserInformation*> allPlayers, UserID attacker, UserID defender, quint8 sizeOfDeck);
    void destructGameInstanceWindow();

};

