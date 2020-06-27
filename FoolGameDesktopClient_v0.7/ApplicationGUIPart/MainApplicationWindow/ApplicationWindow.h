#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H
#include "MenuWindow/MenuWindow.h"
#include "LoadingWindow/LoadingWindow.h"
#include "RegistrationSystem/RegistrationSystem.h"
#include "InstanceGUIPart/GameTable/GameTableWidget.h"
#include "../../ConnectWithServerPart/ApplicationEthernetController.h"
#include "UserInformation/UserInformation.h"
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
    ChatScene* m_chatSceneObject;

    QHBoxLayout* m_layout;
    MenuWindow* m_menuWindow;
    RegistrationSystem* m_registrationMenu;
    LoadingWindow* m_loadingWindow;
    GameTableWidget* m_instanceWindow;

    ApplicationEthernetController* m_ethernetController;

    UserState m_userState;
public:
    explicit ApplicationWindow(QWidget *parent = nullptr);

signals:
    void signalExitButtonWasClicked(bool);

public slots:
    void transitionFromRegistrationWindowToMenu(const QString&, const QString&);
    void transitionFromMenuToRegistrationWindow();

    void transitionFromMenuToLoadingWindow();
    void transitionFromLoadingWindowToMenu();

    void transitionFromLoadingWindowToGameInstance(Card::Suit, Card::Dignity, UserID, QList<UserInformation>, UserID, UserID, quint8);
    void transitionFromGameInstanceToMenu(UserID);



    void slotMakeAlert(const QString&, const QString&);

private:
    void createReistrationWindow();
    void destructRegistrationWindow();

    void createMenuWindow();
    void destructMenuWindow();

    void createLoadingWindow();
    void destructLoadingWindow();

    void createChatScene();
    void destructChatScene();

    void createGameInstanceWindow(Card::Suit trumpS, Card::Dignity trumpD, UserID thisID, QList<UserInformation> allPlayers, UserID attacker, UserID defender, quint8 sizeOfDeck);
    void destructGameInstanceWindow();

protected slots:
    virtual void paintEvent(QPaintEvent*) override;
};

#endif // APPLICATIONWINDOW_H
