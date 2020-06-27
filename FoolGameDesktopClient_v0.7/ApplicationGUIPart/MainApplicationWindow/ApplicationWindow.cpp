#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(QWidget *parent)
    :QWidget{ parent },
     m_chatSceneObject{ nullptr },
     m_layout{ new QHBoxLayout },
     m_menuWindow{ nullptr },
     m_registrationMenu{ nullptr },
     m_loadingWindow{ nullptr },
     m_instanceWindow{ nullptr },
     m_ethernetController{ new ApplicationEthernetController(this) },
     m_userState{ UserState::UserNoSignIn }
    {
        this->setFixedSize(480, 280);
        this->setContentsMargins(QMargins(1, 1, 1, 1));

        createReistrationWindow();
        this->setLayout(m_layout);
    }

void ApplicationWindow::transitionFromRegistrationWindowToMenu(const QString& /*name*/, const QString& /*password*/)
{
    m_userState = UserState::UserInLobbi;
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalApplicationMakeAlert, this, &ApplicationWindow::slotMakeAlert, Qt::ConnectionType::UniqueConnection);
    this->createChatScene();
    this->destructRegistrationWindow();
    this->createMenuWindow();
}
void ApplicationWindow::transitionFromMenuToRegistrationWindow()
{
    m_userState = UserState::UserNoSignIn;
    QObject::disconnect(m_ethernetController, &ApplicationEthernetController::signalApplicationMakeAlert, this, &ApplicationWindow::slotMakeAlert);
    this->destructChatScene();
    this->destructMenuWindow();
    this->createReistrationWindow();
}



void ApplicationWindow::transitionFromMenuToLoadingWindow()
{
    m_userState = UserState::UserWaitGame;
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalApplicationCreateGameInstance, this, &ApplicationWindow::transitionFromLoadingWindowToGameInstance, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::queueSignalUserRemovedFromWaitingRoom, this, &ApplicationWindow::transitionFromLoadingWindowToMenu, Qt::ConnectionType::UniqueConnection);
    this->setFixedSize(480, 280);
    destructMenuWindow();
    createLoadingWindow();
}
void ApplicationWindow::transitionFromLoadingWindowToMenu()
{
    m_userState = UserState::UserInLobbi;
    QObject::disconnect(m_ethernetController, &ApplicationEthernetController::signalApplicationCreateGameInstance, this, &ApplicationWindow::transitionFromLoadingWindowToGameInstance);
    QObject::disconnect(m_ethernetController, &ApplicationEthernetController::queueSignalUserRemovedFromWaitingRoom, this, &ApplicationWindow::transitionFromLoadingWindowToMenu);
    this->setFixedSize(480, 280);
    destructLoadingWindow();
    createMenuWindow();
}

void ApplicationWindow::transitionFromLoadingWindowToGameInstance(Card::Suit trumpS, Card::Dignity trumpD, UserID thisID, QList<UserInformation> allPlayers, UserID attacker, UserID defender, quint8 sizeOfDeck)
{
    m_userState = UserState::UserInGame;
    QObject::disconnect(m_ethernetController, &ApplicationEthernetController::signalApplicationCreateGameInstance, this, &ApplicationWindow::transitionFromLoadingWindowToGameInstance);
    QObject::disconnect(m_ethernetController, &ApplicationEthernetController::signalApplicationMakeAlert, this, &ApplicationWindow::slotMakeAlert);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceEndOfMatch, this, &ApplicationWindow::transitionFromGameInstanceToMenu, Qt::ConnectionType::UniqueConnection);

    this->setFixedSize(520, 680);
    this->destructLoadingWindow();
    this->createGameInstanceWindow(trumpS, trumpD, thisID, allPlayers, attacker, defender, sizeOfDeck);
}
void ApplicationWindow::transitionFromGameInstanceToMenu(UserID winnerID)
{
    m_userState = UserState::UserInLobbi;
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalApplicationMakeAlert, this, &ApplicationWindow::slotMakeAlert, Qt::ConnectionType::UniqueConnection);
    QObject::disconnect(m_ethernetController, &ApplicationEthernetController::signalInstanceEndOfMatch, this, &ApplicationWindow::transitionFromGameInstanceToMenu);

    this->setFixedSize(480, 280);
    this->destructGameInstanceWindow();
    this->createMenuWindow();

    QString title = QString("Winner:");
    QString winner = QString::number(winnerID);
    this->slotMakeAlert(title, winner);
}







void ApplicationWindow::createReistrationWindow()
{
    this->m_registrationMenu = new RegistrationSystem;

    QObject::connect(m_registrationMenu, &RegistrationSystem::playerTryLogIn, m_ethernetController, &ApplicationEthernetController::registrationSlotPlayerLogIn, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_registrationMenu, &RegistrationSystem::playerTryRegistration, m_ethernetController, &ApplicationEthernetController::registrationSlotPlayerRegistration, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_ethernetController, &ApplicationEthernetController::registrationSignalSuccusfullySignIn,          m_registrationMenu, &RegistrationSystem::succesfullySignIn, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::registrationSignalUnsuccusfullySignIn, m_registrationMenu, &RegistrationSystem::unsuccesfullySignIn, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_registrationMenu, &RegistrationSystem::userSignIn, this, &ApplicationWindow::transitionFromRegistrationWindowToMenu, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_registrationMenu, &RegistrationSystem::signalExitButtonWasClicked, this, &ApplicationWindow::signalExitButtonWasClicked, Qt::ConnectionType::UniqueConnection);

    this->m_layout->addWidget(m_registrationMenu);
}
void ApplicationWindow::destructRegistrationWindow()
{
    this->m_registrationMenu->hide();
    this->m_registrationMenu->deleteLater();
    this->m_registrationMenu = nullptr;
}

void ApplicationWindow::createMenuWindow()
{
    this->m_menuWindow = new MenuWindow(m_chatSceneObject);

    QObject::connect(m_menuWindow, &MenuWindow::signalPlayButtonWasClicked, m_ethernetController, &ApplicationEthernetController::applicationSlotPlayerWantPlay, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_ethernetController, &ApplicationEthernetController::queueSignalUserAddedToWaitingRoom, this, &ApplicationWindow::transitionFromMenuToLoadingWindow, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_menuWindow, &MenuWindow::signalPlayButtonWasClicked, m_ethernetController, &ApplicationEthernetController::applicationSlotPlayerWantPlay, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_menuWindow, &MenuWindow::singalPlayerWantsDepositMoney, m_ethernetController, &ApplicationEthernetController::applicationSlotPlayerDepositMoney, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_menuWindow, &MenuWindow::singalPlayerWantsWithdrawMoney, m_ethernetController, &ApplicationEthernetController::applicationSlotPlayerWithdrawMoney, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_menuWindow, &MenuWindow::signalExitButtonWasClicked, m_ethernetController, &ApplicationEthernetController::registrationSlotPlayerLogOut, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::registrationSignalConfirmlogOut, this, &ApplicationWindow::transitionFromMenuToRegistrationWindow, Qt::ConnectionType::UniqueConnection);
    this->m_layout->addWidget(m_menuWindow);
}
void ApplicationWindow::destructMenuWindow()
{
    m_menuWindow->hide();
    m_menuWindow->deleteLater();
    m_menuWindow = nullptr;
}

void ApplicationWindow::createLoadingWindow()
{
    m_loadingWindow = new LoadingWindow;
    QObject::connect(m_loadingWindow, &LoadingWindow::signalExitButtonWasClicked, m_ethernetController, &ApplicationEthernetController::applicationSlotPlayerExitFromWaitingRoom, Qt::ConnectionType::UniqueConnection);
    this->m_layout->addWidget(m_loadingWindow);
}
void ApplicationWindow::destructLoadingWindow()
{
    m_loadingWindow->hide();
    m_loadingWindow->deleteLater();
    m_loadingWindow = nullptr;
}

void ApplicationWindow::createChatScene()
{
    m_chatSceneObject = new ChatScene(QRect(0, 0, 170, 200));
    QObject::connect(m_chatSceneObject->chatWidget(), &ChatWidget::signalSendMessage, m_ethernetController, &ApplicationEthernetController::messageSlotSendMessage, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::messageSignalReceiveUserMessage, m_chatSceneObject->chatWidget(), &ChatWidget::slotReceiveUserMessage, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::messageSignalReceiveServerMessage, m_chatSceneObject->chatWidget(), &ChatWidget::slotReceiveServerMessage, Qt::ConnectionType::UniqueConnection);
}
void ApplicationWindow::destructChatScene()
{
    m_chatSceneObject->deleteLater();
    m_chatSceneObject = nullptr;
}

void ApplicationWindow::createGameInstanceWindow(Card::Suit trumpS, Card::Dignity trumpD, UserID thisID, QList<UserInformation> allPlayers, UserID attacker, UserID defender, quint8 sizeOfDeck)
{
    m_instanceWindow = new GameTableWidget(trumpS, trumpD, thisID, allPlayers, attacker, defender, sizeOfDeck, m_chatSceneObject);

    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstancePlayerBeatCard, m_instanceWindow, &GameTableWidget::serverSlotPlayerBeatCard, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstancePlayerTossedCard, m_instanceWindow, &GameTableWidget::serverSlotPlayerTossedCard, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstancePlayerTransferable, m_instanceWindow, &GameTableWidget::serverSlotPlayerTransferable, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceUnsuccesfullyAction, m_instanceWindow, &GameTableWidget::serverSlotUnsuccesfullyAction, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceMakeTurn, m_instanceWindow, &GameTableWidget::serverSlotMakeTurn, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceSetNewMainPair, m_instanceWindow, &GameTableWidget::serverSlotSetNewMainPair, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstancePlayerTakeAllCards, m_instanceWindow, &GameTableWidget::serverSlotPlayerTakeAllCards, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceThisPlayerTakeCardFromDeck, m_instanceWindow, &GameTableWidget::serverSlotThisPlayerTakeCardFromDeck, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ApplicationEthernetController::signalInstanceOtherPlayerTakeCardFromDeck, m_instanceWindow, &GameTableWidget::serverSlotOtherPlayerTakeCardFromDeck, Qt::ConnectionType::UniqueConnection);


    QObject::connect(m_instanceWindow, &GameTableWidget::tryBeat, m_ethernetController, &ApplicationEthernetController::instanceSlotPlayerTryBeat);
    QObject::connect(m_instanceWindow, &GameTableWidget::tryToss, m_ethernetController, &ApplicationEthernetController::instanceSlotPlayerTryToss);
    QObject::connect(m_instanceWindow, &GameTableWidget::tryTrancferable, m_ethernetController, &ApplicationEthernetController::instanceSlotTryTransferable);
    QObject::connect(m_instanceWindow, &GameTableWidget::actionButtonWasClicked, m_ethernetController, &ApplicationEthernetController::instanceSlotActionButtonWasClicked);









    m_layout->addWidget(m_instanceWindow);
}
void ApplicationWindow::destructGameInstanceWindow()
{
    m_instanceWindow->hide();
    m_instanceWindow->deleteLater();
    m_instanceWindow = nullptr;
}






void ApplicationWindow::slotMakeAlert(const QString& title, const QString& message)
{
    QMessageBox::information(this, title, message);
}
void ApplicationWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(139, 69, 19)));
    painter.drawRect(this->rect());

    painter.setBrush(QBrush(QColor(105, 105, 105)));
    painter.drawRoundedRect(QRect(20, 20, this->width() - 40, this->height() - 40), 15, 15);
}
