#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H
#include "MenuWindow/MenuWindow.h"
#include "RegistrationSystem/RegistrationSystem.h"
#include "InstanceGUIPart/GameTable/GameTableWidget.h"
#include "../../ConnectWithServerPart/ApplicationEthernetController.h"
#include "UserInformation/UserInformation.h"
#include <QStateMachine>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>


class ApplicationWindow : public QWidget
{
    Q_OBJECT
private:
    ChatScene* m_chatSceneObject;


    MenuWindow* m_menuWindow;
    RegistrationSystem* m_registrationMenu;
    GameTableWidget* m_instanceWindow;

    ApplicationEthernetController* m_ethernetController;
    QStateMachine* m_stateMachine;
    QHBoxLayout* m_layout;

public:
    explicit ApplicationWindow(QWidget *parent = nullptr);

signals:
    void signalExitButtonWasClicked(bool);

    void insideSignalChangeMenuState();

public slots:
    void serverSlotCreateGameInstance(Card::Suit, Card::Dignity, UserID, QList<UserInformation>, UserID, UserID, quint8);
    void serverSlotMakeAlert(const QString&, const QString&);
    void serverSlotEndOfMatch();

protected slots:
    virtual void paintEvent(QPaintEvent*) override;
};

#endif // APPLICATIONWINDOW_H
