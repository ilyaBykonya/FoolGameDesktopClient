#ifndef PAYMENTWINDOW_H
#define PAYMENTWINDOW_H
#include "FoolGameApplicationWindow/Files/SettingsStruct.h"
#include "FoolGameApplicationWindow/Files/TypesAliases.h"
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QPainter>
#include <QLabel>
class PaymentWindow : public QWidget
{
    Q_OBJECT
    QComboBox* m_transactionChanger;
    QPushButton* m_addTokens;
    QPushButton* m_subTokens;

    QPushButton* m_exitButton;

public:
    explicit PaymentWindow(QWidget *parent = nullptr);

signals:
    void signalExitButtonWasClicked(bool);
    void singalDepositToWallet(Cash);
    void singalWithdrawFromWallet(Cash);
};

#endif // PAYMENTWINDOW_H
