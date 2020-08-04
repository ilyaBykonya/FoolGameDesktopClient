#include "MenuWindow.h"

MenuWindow::MenuWindow(const QPixmap& avatar, ChatScene* chatScene, QWidget *parent)
    :CustomTabWidget{ parent },
     m_gameSelector{ new GameSelectionWindow(chatScene, this) },
     m_paymentWindow{ new PaymentWindow(this) },
     m_optionsSelector{ new OptionsWindow(avatar, this) }
    {
        this->setContentsMargins(0, 0, 0, 0);

        this->addTab(m_gameSelector, "Play");
        this->addTab(m_paymentWindow, "Wallet");
        this->addTab(m_optionsSelector, "Options");

        //********************************************************

        QObject::connect(m_optionsSelector, &OptionsWindow::signalUserAvatarUpdate,
                         this, &MenuWindow::signalUserAvatarUpdate, Qt::ConnectionType::UniqueConnection);
        QObject::connect(m_optionsSelector, &OptionsWindow::signalExitButtonWasClicked,
                         this, &MenuWindow::signalExitButtonWasClicked, Qt::ConnectionType::UniqueConnection);



        QObject::connect(m_paymentWindow, &PaymentWindow::signalExitButtonWasClicked,
                         this, &MenuWindow::signalExitButtonWasClicked, Qt::ConnectionType::UniqueConnection);
        QObject::connect(m_paymentWindow, &PaymentWindow::singalDepositToWallet,
                         this, &MenuWindow::singalDepositToWallet, Qt::ConnectionType::UniqueConnection);
        QObject::connect(m_paymentWindow, &PaymentWindow::singalWithdrawFromWallet,
                         this, &MenuWindow::singalWithdrawFromWallet, Qt::ConnectionType::UniqueConnection);



        QObject::connect(m_gameSelector, &GameSelectionWindow::signalPlayButtonWasClicked, [&]()
        {
            emit signalPlayButtonWasClicked(m_optionsSelector->allSettings());
        });
        QObject::connect(m_gameSelector, &GameSelectionWindow::signalExitButtonWasClicked,
                         this, &MenuWindow::signalExitButtonWasClicked, Qt::ConnectionType::UniqueConnection);


     }
