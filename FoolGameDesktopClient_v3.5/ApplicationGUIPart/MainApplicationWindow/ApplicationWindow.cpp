#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(QWidget *parent)
    :QWidget{ parent },
     m_menuWindow{ new MenuWindow(this) },
     m_registrationMenu{ new RegistrationSystem },
     m_instanceWindow{ nullptr },
     m_ethernetController{ new ApplicationEthernetController(this) },
     m_stateMachine{ new QStateMachine(this) },
     m_layout{ new QHBoxLayout }
    {
        this->setContentsMargins(QMargins(1, 1, 1, 1));
        QPalette pall = this->palette();
        pall.setColor(QPalette::ColorRole::Background, QColor(105, 105, 105));
        this->setPalette(pall);

        QState* stateRegistrationWindowActive = new QState(m_stateMachine);
        stateRegistrationWindowActive->assignProperty(this, "size", QSize(400, 300));
        stateRegistrationWindowActive->assignProperty(m_registrationMenu, "visible", true);
        stateRegistrationWindowActive->assignProperty(m_registrationMenu, "geometry", this->rect());
        stateRegistrationWindowActive->assignProperty(m_menuWindow, "visible", false);
        m_stateMachine->setInitialState(stateRegistrationWindowActive);

        QState* stateMenuWindowActive = new QState(m_stateMachine);
        stateMenuWindowActive->assignProperty(this, "geometry", QSize(400, 300));
        stateMenuWindowActive->assignProperty(m_menuWindow, "visible", true);
        stateMenuWindowActive->assignProperty(m_menuWindow, "geometry", this->rect());
        stateMenuWindowActive->assignProperty(m_registrationMenu, "visible", false);

        QState* stateGameInstanceActive = new QState(m_stateMachine);
        stateGameInstanceActive->assignProperty(this, "geometry", QSize(620, 620));
        stateGameInstanceActive->assignProperty(m_registrationMenu, "visible", false);
        stateGameInstanceActive->assignProperty(m_menuWindow, "visible", false);


        stateRegistrationWindowActive->addTransition(m_registrationMenu, &RegistrationSystem::playerSignIn, stateMenuWindowActive);
        stateMenuWindowActive->addTransition(m_menuWindow, &MenuWindow::signalPlayButtonWasClicked, stateGameInstanceActive);
        stateMenuWindowActive->addTransition(m_menuWindow, &MenuWindow::signalExitButtonWasClicked, stateRegistrationWindowActive);
        stateGameInstanceActive->addTransition(this, &ApplicationWindow::insideSignalChangeMenuState, stateMenuWindowActive);

        m_layout->addWidget(m_registrationMenu);
        m_layout->addWidget(m_menuWindow);
        this->setLayout(m_layout);

        QObject::connect(m_registrationMenu, &RegistrationSystem::playerTryLogIn, m_ethernetController, &ApplicationEthernetController::registrationSlotPlayerLogIn);
        QObject::connect(m_registrationMenu, &RegistrationSystem::playerTryRegistration, m_ethernetController, &ApplicationEthernetController::registrationSlotPlayerRegistration);
        QObject::connect(m_ethernetController, &ApplicationEthernetController::registrationSignalSuccusfullyLogIn,          m_registrationMenu, &RegistrationSystem::succesfullyLogIn);
        QObject::connect(m_ethernetController, &ApplicationEthernetController::registrationSignalUnsuccusfullyLogIn,        m_registrationMenu, &RegistrationSystem::unsuccesfullyLogIn);
        QObject::connect(m_ethernetController, &ApplicationEthernetController::registrationSignalSuccusfullyRegistration,   m_registrationMenu, &RegistrationSystem::succesfullyRegistration);
        QObject::connect(m_ethernetController, &ApplicationEthernetController::registrationSignalUnsuccusfullyRegistration, m_registrationMenu, &RegistrationSystem::unsuccesfullyRegistration);
        QObject::connect(m_registrationMenu, &RegistrationSystem::signalExitButtonWasClicked, this, &ApplicationWindow::signalExitButtonWasClicked);


        QObject::connect(m_menuWindow, &MenuWindow::signalPlayButtonWasClicked, m_ethernetController, &ApplicationEthernetController::applicationSlotPlayerWantPlay);
        QObject::connect(m_menuWindow, &MenuWindow::singalPlayerWantsDepositMoney, m_ethernetController, &ApplicationEthernetController::applicationSlotPlayerDepositMoney);
        QObject::connect(m_menuWindow, &MenuWindow::singalPlayerWantsWithdrawMoney, m_ethernetController, &ApplicationEthernetController::applicationSlotPlayerWithdrawMoney);;


        QObject::connect(m_ethernetController, &ApplicationEthernetController::signalApplicationCreateGameInstance, this, &ApplicationWindow::serverSlotCreateGameInstance);
        QObject::connect(m_ethernetController, &ApplicationEthernetController::signalApplicationMakeAlert, this, &ApplicationWindow::serverSlotMakeAlert);
        QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceEndOfMatch, this, &ApplicationWindow::serverSlotEndOfMatch);

        QObject::connect(m_ethernetController, &ApplicationEthernetController::messageSignalReceiveMessage, m_menuWindow, &MenuWindow::messageSignalReceiveMessage);
        QObject::connect(m_menuWindow, &MenuWindow::messageSignalSendMessage, m_ethernetController, &ApplicationEthernetController::messageSlotSendMessage);

        m_stateMachine->start();
    }

void ApplicationWindow::serverSlotCreateGameInstance(Card::Suit trumpS, Card::Dignity trumpD, qint16 thisID, QList<qint16> allPlayersID, qint16 attacker, qint16 defender, qint16 sizeOfDeck)
{
    m_instanceWindow = new GameTableWidget(trumpS, trumpD, thisID, allPlayersID, attacker, defender, sizeOfDeck);

    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceMakeTurn, m_instanceWindow, &GameTableWidget::serverSlotMakeTurn);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstancePlayerBeatCard, m_instanceWindow, &GameTableWidget::serverSlotPlayerBeatCard);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceSetNewMainPair, m_instanceWindow, &GameTableWidget::serverSlotSetNewMainPair);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstancePlayerTossedCard, m_instanceWindow, &GameTableWidget::serverSlotPlayerTossedCard);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstancePlayerTransferable, m_instanceWindow, &GameTableWidget::serverSlotPlayerTransferable);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstancePlayerTakeAllCards, m_instanceWindow, &GameTableWidget::serverSlotPlayerTakeAllCards);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceThisPlayerTakeCardFromDeck, m_instanceWindow, &GameTableWidget::serverSlotThisPlayerTakeCardFromDeck);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceOtherPlayerTakeCardFromDeck, m_instanceWindow, &GameTableWidget::serverSlotOtherPlayerTakeCardFromDeck);

    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceUnsuccesfullyAction, m_instanceWindow, &GameTableWidget::serverSlotUnsuccesfullyAction);


    QObject::connect(m_instanceWindow, &GameTableWidget::tryBeat, m_ethernetController, &ApplicationEthernetController::instanceSlotPlayerTryBeat);
    QObject::connect(m_instanceWindow, &GameTableWidget::tryToss, m_ethernetController, &ApplicationEthernetController::instanceSlotPlayerTryToss);
    QObject::connect(m_instanceWindow, &GameTableWidget::tryTrancferable, m_ethernetController, &ApplicationEthernetController::instanceSlotTryTransferable);
    QObject::connect(m_instanceWindow, &GameTableWidget::actionButtonWasClicked, m_ethernetController, &ApplicationEthernetController::instanceSlotActionButtonWasClicked);

    QObject::connect(m_instanceWindow, &GameTableWidget::messageSignalSendMessage, m_ethernetController, &ApplicationEthernetController::messageSlotSendMessage, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::messageSignalReceiveMessage, m_instanceWindow, &GameTableWidget::messageSignalReceiveMessage, Qt::ConnectionType::UniqueConnection);


    m_layout->addWidget(m_instanceWindow);
    m_instanceWindow->update();
    this->resize(620, 620);
}
void ApplicationWindow::serverSlotMakeAlert(const QString& title, const QString& message)
{
    QMessageBox::information(this, title, message);
}
void ApplicationWindow::serverSlotEndOfMatch()
{
    m_instanceWindow->hide();
    m_instanceWindow->deleteLater();

    emit insideSignalChangeMenuState();
    this->resize(400, 300);
}

void ApplicationWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(139, 69, 19)));
    painter.drawRect(this->rect());

    painter.setBrush(QBrush(QColor(105, 105, 105)));
    painter.drawRoundedRect(QRect(20, 20, this->width() - 40, this->height() - 40), 15, 15);
}
