#include "MenuWindow.h"

MenuWindow::MenuWindow(ChatScene* chatScene, QWidget *parent)
    :CustomTabWidget{ parent },
     m_gameSelector{ new GameSelectionWindow(chatScene, this) },
     m_paymentWindow{ new PaymentWindow(this) },
     m_optionsSelector{ new OptionsWindow(this) }
    {
        this->addTab(m_gameSelector, "Play");
        this->addTab(m_paymentWindow, "Wallet");
        this->addTab(m_optionsSelector, "Options");

        //********************************************************
        //options
        //Шрифт. Желательно выбрать другой
        this->setFont(QFont("Perpetua Titling MT", 9, 3));
        QPalette pall;
        pall.setColor(QPalette::ColorRole::ButtonText, QColor(128, 0, 0));
        this->setPalette(pall);

        QObject::connect(m_optionsSelector, &OptionsWindow::signalExitButtonWasClicked, this, &MenuWindow::signalExitButtonWasClicked);

        QObject::connect(m_paymentWindow, &PaymentWindow::signalExitButtonWasClicked, this, &MenuWindow::signalExitButtonWasClicked);
        QObject::connect(m_paymentWindow, &PaymentWindow::signalUserAddCash, this, &MenuWindow::singalPlayerWantsDepositMoney);
        QObject::connect(m_paymentWindow, &PaymentWindow::signalUserSubCash, this, &MenuWindow::singalPlayerWantsWithdrawMoney);

        QObject::connect(m_gameSelector, &GameSelectionWindow::signalPlayButtonWasClicked, [&]()
        {
            emit signalPlayButtonWasClicked(m_optionsSelector->allSettings(), QPair<quint32, quint32>(m_gameSelector->minimumCash(), m_gameSelector->maximumCash()));
        });
        QObject::connect(m_gameSelector, &GameSelectionWindow::signalExitButtonWasClicked, this, &MenuWindow::signalExitButtonWasClicked);
     }

void MenuWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(105, 105, 105)));
        painter.drawRect(this->rect());
}
