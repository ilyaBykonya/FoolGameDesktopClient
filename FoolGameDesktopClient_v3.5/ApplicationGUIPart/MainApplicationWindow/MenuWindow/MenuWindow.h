#ifndef DEFAULTWINDOW_H
#define DEFAULTWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QGridLayout>
#include "CustomTabWidget/CustomTabWidget.h"
#include "OptionsWindow/OptionsWindow.h"
#include "PaymentWindow/PaymentWindow.h"
#include "GameSelectionWindow/GameSelectionWindow.h"

class MenuWindow : public CustomTabWidget
{
    Q_OBJECT
private:
    GameSelectionWindow* m_gameSelector;
    PaymentWindow* m_paymentWindow;
    OptionsWindow* m_optionsSelector;
public:
    explicit MenuWindow(QWidget *parent = nullptr);

signals:
    void messageSignalReceiveMessage(ChatWindow::Canal, const QString&);
    void messageSignalSendMessage(ChatWindow::Canal, const QString&);


    void signalPlayButtonWasClicked(quint8, quint8, bool);

    void singalPlayerWantsDepositMoney(qint16);
    void singalPlayerWantsWithdrawMoney(qint16);

    void signalExitButtonWasClicked(bool);

protected slots:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // DEFAULTWINDOW_H