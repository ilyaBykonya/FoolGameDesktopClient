#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(const QString& hostAddress, quint16 portNumber, QWidget *parent)
    :QWidget{ parent },
     m_ethernetController{ new ServerConnector(hostAddress, portNumber, this) },
     m_thisUserFullInfo{ nullptr },
     m_layout{ new QVBoxLayout },
     m_chatSceneObject{ nullptr },
     m_statusBar{ nullptr },
     m_registrationMenu{ nullptr },
     m_menuWindow{ nullptr },
     m_loadingWindow{ nullptr },
     m_instanceWindow{ nullptr },
     m_userState{ UserState::UserNoSignIn }
    {
        this->setObjectName("ApplicationWindow");
        this->setFixedSize(480, 280);
        this->setContentsMargins(QMargins(1, 1, 1, 1));

        createReistrationWindow();

        m_layout->setSpacing(0);
        m_layout->setMargin(0);
        this->setLayout(m_layout);
    }

void ApplicationWindow::transitionFromRegistrationWindowToMenu(UserID id, const QString& name, Cash gameMoney, Cash realMoney, quint32 countOfGames, quint32 raitingPoints, const QPixmap& avatar)
{
    m_userState = UserState::UserInLobbi;
    QObject::connect(m_ethernetController, &ServerConnector::signalUpdateThisUserFullInformation,
                     this, &ApplicationWindow::slotUpdateUserInfo, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::signalApplicationMakeAlert,
                     this, &ApplicationWindow::slotMakeAlert, Qt::ConnectionType::UniqueConnection);
    this->createUserFullInfo(id, name, gameMoney, realMoney, countOfGames, raitingPoints, avatar);
    this->createStatusBar(m_thisUserFullInfo);
    this->createChatScene();
    this->destructRegistrationWindow();
    this->createMenuWindow();
}
void ApplicationWindow::transitionFromMenuToRegistrationWindow()
{
    m_userState = UserState::UserNoSignIn;
    QObject::disconnect(m_ethernetController, &ServerConnector::signalApplicationMakeAlert, this, &ApplicationWindow::slotMakeAlert);
    this->destructChatScene();
    this->destructMenuWindow();
    this->destructStatusBar();
    this->createReistrationWindow();
}



void ApplicationWindow::transitionFromMenuToLoadingWindow()
{
    m_userState = UserState::UserWaitGame;
    QObject::connect(m_ethernetController, &ServerConnector::signalApplicationCreateGameInstance, this, &ApplicationWindow::transitionFromLoadingWindowToGameInstance, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::queueSignalUserRemovedFromWaitingRoom, this, &ApplicationWindow::transitionFromLoadingWindowToMenu, Qt::ConnectionType::UniqueConnection);
    this->setFixedSize(480, 280);
    destructMenuWindow();
    createLoadingWindow();
}
void ApplicationWindow::transitionFromLoadingWindowToMenu()
{
    m_userState = UserState::UserInLobbi;
    QObject::disconnect(m_ethernetController, &ServerConnector::signalApplicationCreateGameInstance, this, &ApplicationWindow::transitionFromLoadingWindowToGameInstance);
    QObject::disconnect(m_ethernetController, &ServerConnector::queueSignalUserRemovedFromWaitingRoom, this, &ApplicationWindow::transitionFromLoadingWindowToMenu);
    this->setFixedSize(480, 280);
    destructLoadingWindow();
    createMenuWindow();
}

void ApplicationWindow::transitionFromLoadingWindowToGameInstance(Card::Suit trumpS, Card::Dignity trumpD, UserID thisID, QList<GameUserInformation*> allPlayers, UserID attacker, UserID defender, quint8 sizeOfDeck)
{
    m_userState = UserState::UserInGame;
    QObject::disconnect(m_ethernetController, &ServerConnector::signalApplicationCreateGameInstance, this, &ApplicationWindow::transitionFromLoadingWindowToGameInstance);
    QObject::disconnect(m_ethernetController, &ServerConnector::signalApplicationMakeAlert, this, &ApplicationWindow::slotMakeAlert);
    QObject::connect(m_ethernetController, &ServerConnector::signalInstanceEndOfMatch, this, &ApplicationWindow::transitionFromGameInstanceToMenu, Qt::ConnectionType::UniqueConnection);

    this->setFixedSize(520, 680);
    this->destructLoadingWindow();
    this->createGameInstanceWindow(trumpS, trumpD, thisID, allPlayers, attacker, defender, sizeOfDeck);
}
void ApplicationWindow::transitionFromGameInstanceToMenu(QList<GameUserInformation*> winnersList)
{
    m_userState = UserState::UserInLobbi;
    QObject::connect(m_ethernetController, &ServerConnector::signalApplicationMakeAlert, this, &ApplicationWindow::slotMakeAlert, Qt::ConnectionType::UniqueConnection);
    QObject::disconnect(m_ethernetController, &ServerConnector::signalInstanceEndOfMatch, this, &ApplicationWindow::transitionFromGameInstanceToMenu);

    this->setFixedSize(480, 280);
    this->destructGameInstanceWindow();
    this->createMenuWindow();

    QString title = QString("Winners:\n");
    QString info;
    for(auto it = winnersList.begin(); it != winnersList.end(); ++it)
    {
        info.append(QString("%1 [%2]\n").arg((*it)->userName()).arg((*it)->userID()));
        (*it)->deleteLater();
    }
    this->slotMakeAlert(title, info);
}






void ApplicationWindow::createChatScene()
{
    m_chatSceneObject = new ChatScene(QRect(0, 0, 170, 200));
    QObject::connect(m_chatSceneObject->chatWidget(), &ChatWidget::signalSendMessage,
                     m_ethernetController, &ServerConnector::messageSlotSendMessage, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_ethernetController, &ServerConnector::messageSignalReceiveUserMessage,
                     m_chatSceneObject->chatWidget(), &ChatWidget::slotReceiveUserMessage, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::messageSignalReceiveServerMessage,
                     m_chatSceneObject->chatWidget(), &ChatWidget::slotReceiveServerMessage, Qt::ConnectionType::UniqueConnection);
}
void ApplicationWindow::destructChatScene()
{
    m_chatSceneObject->deleteLater();
    m_chatSceneObject = nullptr;
}



void ApplicationWindow::createStatusBar(ThisUserFullInformation* userInfo)
{
    m_statusBar = new StatusBar(userInfo);
    m_layout->addWidget(m_statusBar, 0, Qt::AlignmentFlag::AlignTop);
}
void ApplicationWindow::destructStatusBar()
{
    m_statusBar->hide();
    m_statusBar->deleteLater();
    m_statusBar = nullptr;
}

void ApplicationWindow::createUserFullInfo(UserID id, const QString& name, Cash dollars, Cash tokens, quint32 countOfGames, quint32 raitingPoints, const QPixmap& avatar)
{
    m_thisUserFullInfo = new ThisUserFullInformation(id, name, dollars, tokens, countOfGames, raitingPoints, avatar, this);
}
void ApplicationWindow::destructUserFullInfo()
{
    m_thisUserFullInfo->deleteLater();
    m_thisUserFullInfo = nullptr;
}





void ApplicationWindow::createReistrationWindow()
{
    this->m_registrationMenu = new RegistrationSystem;

    QObject::connect(m_registrationMenu, &RegistrationSystem::playerTryLogIn, m_ethernetController, &ServerConnector::registrationSlotPlayerLogIn, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_registrationMenu, &RegistrationSystem::playerTryRegistration, m_ethernetController, &ServerConnector::registrationSlotPlayerRegistration, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_registrationMenu, &RegistrationSystem::signalExitButtonWasClicked, this, &ApplicationWindow::signalExitButtonWasClicked, Qt::ConnectionType::UniqueConnection);


    QObject::connect(m_ethernetController, &ServerConnector::registrationSignalSuccusfullySignIn, m_registrationMenu, &RegistrationSystem::succesfullySignIn, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::registrationSignalUnsuccusfullySignIn, m_registrationMenu, &RegistrationSystem::unsuccesfullySignIn, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::registrationSignalSuccusfullySignIn, this, &ApplicationWindow::transitionFromRegistrationWindowToMenu, Qt::ConnectionType::UniqueConnection);


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
    this->m_menuWindow = new MenuWindow(this->m_thisUserFullInfo->userAvatar(), m_chatSceneObject);

    QObject::connect(m_menuWindow, &MenuWindow::signalUserAvatarUpdate,
                     m_ethernetController, &ServerConnector::slotUpdateUserAvatar, Qt::ConnectionType::UniqueConnection);


    QObject::connect(m_menuWindow, &MenuWindow::signalPlayButtonWasClicked, m_ethernetController, &ServerConnector::applicationSlotPlayerWantPlay, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_ethernetController, &ServerConnector::queueSignalUserAddedToWaitingRoom, this, &ApplicationWindow::transitionFromMenuToLoadingWindow, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_menuWindow, &MenuWindow::signalPlayButtonWasClicked, m_ethernetController, &ServerConnector::applicationSlotPlayerWantPlay, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_menuWindow, &MenuWindow::singalDepositToWallet, m_ethernetController, &ServerConnector::financeSlotPlayerDepositWallet, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_menuWindow, &MenuWindow::singalWithdrawFromWallet, m_ethernetController, &ServerConnector::financeSlotPlayerWithdrawWallet, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_menuWindow, &MenuWindow::signalExitButtonWasClicked, m_ethernetController, &ServerConnector::registrationSlotPlayerLogOut, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::registrationSignalConfirmLogOut, this, &ApplicationWindow::transitionFromMenuToRegistrationWindow, Qt::ConnectionType::UniqueConnection);
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
    QObject::connect(m_loadingWindow, &LoadingWindow::signalExitButtonWasClicked,
                     m_ethernetController, &ServerConnector::applicationSlotPlayerExitFromWaitingRoom, Qt::ConnectionType::UniqueConnection);
    this->m_layout->addWidget(m_loadingWindow);
}
void ApplicationWindow::destructLoadingWindow()
{
    m_loadingWindow->hide();
    m_loadingWindow->deleteLater();
    m_loadingWindow = nullptr;
}

void ApplicationWindow::createGameInstanceWindow(Card::Suit trumpS, Card::Dignity trumpD, UserID thisID, QList<GameUserInformation*> allPlayersInfo, UserID attacker, UserID defender, DeckSize sizeOfDeck)
{
    m_instanceWindow = new GameTableWidget(trumpS, trumpD, thisID, allPlayersInfo, attacker, defender, sizeOfDeck);

    QObject::connect(m_ethernetController, &ServerConnector::signalInstancePlayerBeatCard, m_instanceWindow, &GameTableWidget::serverSlotPlayerBeatCard, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::signalInstancePlayerTossedCard, m_instanceWindow, &GameTableWidget::serverSlotPlayerTossedCard, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::signalInstancePlayerTransferable, m_instanceWindow, &GameTableWidget::serverSlotPlayerTransferable, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::signalInstanceUnsuccesfullyAction, m_instanceWindow, &GameTableWidget::serverSlotUnsuccesfullyAction, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_ethernetController, &ServerConnector::signalInstanceMakeTurn, m_instanceWindow, &GameTableWidget::serverSlotMakeTurn, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::signalInstanceSetNewMainPair, m_instanceWindow, &GameTableWidget::serverSlotSetNewMainPair, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::signalInstancePlayerTakeAllCards, m_instanceWindow, &GameTableWidget::serverSlotPlayerTakeAllCards, Qt::ConnectionType::UniqueConnection);

    QObject::connect(m_ethernetController, &ServerConnector::signalInstanceThisPlayerTakeCardFromDeck, m_instanceWindow, &GameTableWidget::serverSlotThisPlayerTakeCardFromDeck, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_ethernetController, &ServerConnector::signalInstanceOtherPlayerTakeCardFromDeck, m_instanceWindow, &GameTableWidget::serverSlotOtherPlayerTakeCardFromDeck, Qt::ConnectionType::UniqueConnection);


    QObject::connect(m_instanceWindow, &GameTableWidget::tryBeat, m_ethernetController, &ServerConnector::instanceSlotPlayerTryBeat, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_instanceWindow, &GameTableWidget::tryToss, m_ethernetController, &ServerConnector::instanceSlotPlayerTryToss, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_instanceWindow, &GameTableWidget::tryTrancferable, m_ethernetController, &ServerConnector::instanceSlotTryTransferable, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_instanceWindow, &GameTableWidget::actionButtonWasClicked, m_ethernetController, &ServerConnector::instanceSlotActionButtonWasClicked, Qt::ConnectionType::UniqueConnection);



    m_layout->addWidget(m_instanceWindow);
}
void ApplicationWindow::destructGameInstanceWindow()
{
    m_instanceWindow->hide();
    m_instanceWindow->deleteLater();
    m_instanceWindow = nullptr;
}






void ApplicationWindow::slotUpdateUserInfo(const QString& name, Cash dollars, Cash tokens, quint32 countOfGames, quint32 raitingPoints)
{
    this->m_thisUserFullInfo->setName(name);
    this->m_thisUserFullInfo->setDollars(dollars);
    this->m_thisUserFullInfo->setTokens(tokens);
    this->m_thisUserFullInfo->setCountOfGames(countOfGames);
    this->m_thisUserFullInfo->setRaitingPoints(raitingPoints);

    this->m_statusBar->slotUpdateInformation(this->m_thisUserFullInfo);
}
void ApplicationWindow::slotMakeAlert(const QString& title, const QString& message)
{
    QMessageBox::information(this, title, message);
}

