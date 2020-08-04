#ifndef DEFAULTWINDOW_H
#define DEFAULTWINDOW_H
#include "FoolGameApplicationWindow/Widgets/PermanentWidgets/CustomTabWidget/CustomTabWidget.h"
#include "FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatScene/ChatScene.h"
#include "FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatView/ChatView.h"
#include "FoolGameApplicationWindow/Files/SettingsStruct.h"
#include "FoolGameApplicationWindow/Files/TypesAliases.h"
#include "GameSelectionWindow/GameSelectionWindow.h"
#include "OptionsWindow/OptionsWindow.h"
#include "PaymentWindow/PaymentWindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QPainter>

class MenuWindow : public CustomTabWidget
{
    Q_OBJECT
private:
    GameSelectionWindow* m_gameSelector;
    PaymentWindow* m_paymentWindow;
    OptionsWindow* m_optionsSelector;

public:
    explicit MenuWindow(const QPixmap&, ChatScene*, QWidget *parent = nullptr);

signals:
    void signalPlayButtonWasClicked(SettingsStruct);

    void singalDepositToWallet(Cash);
    void singalWithdrawFromWallet(Cash);

    void signalUserAvatarUpdate(const QPixmap&);

    void signalExitButtonWasClicked(bool);
};

#endif // DEFAULTWINDOW_H
