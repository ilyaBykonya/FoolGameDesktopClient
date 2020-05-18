#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(QWidget *parent)
    :QWidget(parent/*, Qt::WindowType::FramelessWindowHint*/),
     m_defaultWindow{ new DefaultWindow },
     m_optionsMenu{ new OptionsWindow },
     m_paymentMenu{ new PaymentWindow },
     m_registrationMenu{ new RegistrationWindow },
     m_instanceWindow{ nullptr },
     m_ethernetController{ new ApplicationEthernetController(this) },
     m_stateMachine{ new QStateMachine(this) },
     m_layout{ new QHBoxLayout }
    {
        QPalette pall = this->palette();
        pall.setColor(QPalette::ColorRole::Background, QColor(105, 105, 105));
        this->setPalette(pall);

        QState* stateRegistrationWindowActive = new QState(m_stateMachine);
        stateRegistrationWindowActive->assignProperty(m_registrationMenu, "visible", true);
        stateRegistrationWindowActive->assignProperty(m_registrationMenu, "geometry", this->rect());
        stateRegistrationWindowActive->assignProperty(m_defaultWindow, "visible", false);
        stateRegistrationWindowActive->assignProperty(m_paymentMenu, "visible", false);
        stateRegistrationWindowActive->assignProperty(m_optionsMenu, "visible", false);
        m_stateMachine->setInitialState(stateRegistrationWindowActive);

        QState* stateDefaultWindowActive = new QState(m_stateMachine);
        stateDefaultWindowActive->assignProperty(m_defaultWindow, "visible", true);
        stateDefaultWindowActive->assignProperty(m_defaultWindow, "geometry", this->rect());
        stateDefaultWindowActive->assignProperty(m_optionsMenu, "visible", false);
        stateDefaultWindowActive->assignProperty(m_paymentMenu, "visible", false);
        stateDefaultWindowActive->assignProperty(m_registrationMenu, "visible", false);

        QState* stateOptionsWindowActive = new QState(m_stateMachine);
        stateOptionsWindowActive->assignProperty(m_optionsMenu, "visible", true);
        stateOptionsWindowActive->assignProperty(m_optionsMenu, "geometry", this->rect());
        stateOptionsWindowActive->assignProperty(m_registrationMenu, "visible", false);
        stateOptionsWindowActive->assignProperty(m_defaultWindow, "visible", false);
        stateOptionsWindowActive->assignProperty(m_paymentMenu, "visible", false);

        QState* statePaymentWindowActive = new QState(m_stateMachine);
        statePaymentWindowActive->assignProperty(m_paymentMenu, "visible", true);
        statePaymentWindowActive->assignProperty(m_paymentMenu, "geometry", this->rect());
        statePaymentWindowActive->assignProperty(m_registrationMenu, "visible", false);
        statePaymentWindowActive->assignProperty(m_defaultWindow, "visible", false);
        statePaymentWindowActive->assignProperty(m_optionsMenu, "visible", false);

        QState* stateGameInstanceActive = new QState(m_stateMachine);
        stateGameInstanceActive->assignProperty(m_registrationMenu, "visible", false);
        stateGameInstanceActive->assignProperty(m_defaultWindow, "visible", false);
        stateGameInstanceActive->assignProperty(m_optionsMenu, "visible", false);
        stateGameInstanceActive->assignProperty(m_paymentMenu, "visible", false);


        stateRegistrationWindowActive->addTransition(m_registrationMenu, &RegistrationWindow::signalUserRegistration, stateDefaultWindowActive);
        statePaymentWindowActive->addTransition(m_paymentMenu, &PaymentWindow::signalExitButtonWasClicked, stateDefaultWindowActive);
        stateOptionsWindowActive->addTransition(m_optionsMenu, &OptionsWindow::signalExitButtonWasClicked, stateDefaultWindowActive);

        stateDefaultWindowActive->addTransition(m_defaultWindow, &DefaultWindow::signalPaymentButtonWasCLicked, statePaymentWindowActive);
        stateDefaultWindowActive->addTransition(m_defaultWindow, &DefaultWindow::signalOptionsButtonWasCLicked, stateOptionsWindowActive);
        stateDefaultWindowActive->addTransition(m_defaultWindow, &DefaultWindow::signalPlayButtonWasCLicked, stateGameInstanceActive);


        m_layout->addWidget(m_registrationMenu);
        m_layout->addWidget(m_defaultWindow);
        m_layout->addWidget(m_optionsMenu);
        m_layout->addWidget(m_paymentMenu);
        this->setLayout(m_layout);

        QObject::connect(m_defaultWindow, &DefaultWindow::signalPlayButtonWasCLicked, m_ethernetController, &ApplicationEthernetController::instanceSlotPlayerWantPlay);
        QObject::connect(m_defaultWindow, &DefaultWindow::signalExitButtonWasClicked, this, &ApplicationWindow::signalExitButtonWasClicked);
        QObject::connect(m_ethernetController, &ApplicationEthernetController::signalCreateGameInstance, this, &ApplicationWindow::slotCreateGameInstance);

        m_stateMachine->start();
    }

void ApplicationWindow::slotCreateGameInstance(Card::Suit s, Card::Dignity d, qint16 thisID, QList<qint16> idList, qint16 att, qint16 def)
{
    m_instanceWindow = new GameTableWidget(s, d, thisID, idList, att, def);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalPlayerTakeAllCards, m_instanceWindow, &GameTableWidget::serverSlotPlayerTakeAllCards);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalMakeTurn, m_instanceWindow, &GameTableWidget::serverSlotMakeTurn);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalSetNewMainPair, m_instanceWindow, &GameTableWidget::serverSlotSetNewMainPair);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalPlayerTossedCard, m_instanceWindow, &GameTableWidget::serverSlotPlayerTossedCard);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalPlayerBeatCard, m_instanceWindow, &GameTableWidget::serverSlotPlayerBeatCard);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalThisPlayerTakeCardFromDeck, m_instanceWindow, &GameTableWidget::serverSlotThisPlayerTakeCardFromDeck);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalOtherPlayerTakeCardFromDeck, m_instanceWindow, &GameTableWidget::serverSlotOtherPlayerTakeCardFromDeck);


    QObject::connect(m_instanceWindow, &GameTableWidget::tryBeat, m_ethernetController, &ApplicationEthernetController::instanceSlotPlayerTryBeat);
    QObject::connect(m_instanceWindow, &GameTableWidget::tryToss, m_ethernetController, &ApplicationEthernetController::instanceSlotPlayerTryToss);
    QObject::connect(m_instanceWindow, &GameTableWidget::actionButtonWasClicked, m_ethernetController, &ApplicationEthernetController::instanceSlotActionButtonWasClicked);
    m_layout->addWidget(m_instanceWindow);
}
