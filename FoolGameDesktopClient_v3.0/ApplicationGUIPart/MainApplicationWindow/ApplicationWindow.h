#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QWidget>
#include "MenuWindow/MenuWindow.h"
#include "RegistrationWindow/RegistrationWindow.h"
#include "../../ConnectWithServerPart/ApplicationEthernetController.h"
#include <QStateMachine>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

class ApplicationWindow : public QWidget
{
    Q_OBJECT
private:
    MenuWindow* m_menuWindow;
    RegistrationWindow* m_registrationMenu;
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
    void serverSlotCreateGameInstance(Card::Suit, Card::Dignity, qint16, QList<qint16>, qint16, qint16, qint16);
    void serverSlotMakeAlert(const QString&, const QString&);
    void serverSlotEndOfMatch();

protected slots:
    virtual void paintEvent(QPaintEvent*) override;
};

#endif // APPLICATIONWINDOW_H
