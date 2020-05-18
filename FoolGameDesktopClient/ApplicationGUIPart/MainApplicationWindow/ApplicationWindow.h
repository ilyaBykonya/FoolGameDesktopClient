#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QWidget>
#include "DefaultWindow/DefaultWindow.h"
#include "OptionsWindow/OptionsWindow.h"
#include "PaymentWindow/PaymentWindow.h"
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
    DefaultWindow* m_defaultWindow;
    OptionsWindow* m_optionsMenu;
    PaymentWindow* m_paymentMenu;
    RegistrationWindow* m_registrationMenu;
    GameTableWidget* m_instanceWindow;

    ApplicationEthernetController* m_ethernetController;
    QStateMachine* m_stateMachine;
    QHBoxLayout* m_layout;
public:
    explicit ApplicationWindow(QWidget *parent = nullptr);

signals:
    void signalExitButtonWasClicked(bool);

public slots:
    void slotCreateGameInstance(Card::Suit, Card::Dignity, qint16, QList<qint16>, qint16, qint16);
};

#endif // APPLICATIONWINDOW_H
