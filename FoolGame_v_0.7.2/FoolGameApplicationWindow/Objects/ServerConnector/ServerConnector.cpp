#include "ServerConnector.h"


ServerConnector::ServerConnector(const QString& hostAddress, quint16 portNumber, QObject* parent)
    :QObject{ parent },
     m_webSocket{ new QWebSocket(QString("ws://%1:%2").arg(hostAddress).arg(portNumber), QWebSocketProtocol::Version::VersionLatest, this) }
    {
        m_webSocket->open(QUrl(QString("ws://%1:%2").arg(hostAddress).arg(portNumber)));
        QObject::connect(m_webSocket, &QWebSocket::binaryMessageReceived, this, &ServerConnector::serverSlotReadyRead);
        QObject::connect(m_webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(serverSlotError(QAbstractSocket::SocketError)));
    }

void ServerConnector::instanceSlotActionButtonWasClicked()
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppInstToServInst
              << EthernetSignals::ClientSignal::Signals::TableSignal::ActionButtonWasClicked;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}
void ServerConnector::instanceSlotPlayerTryBeat(PairID pairID, Card::Suit cardSuit, Card::Dignity cardDignity)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppInstToServInst
              << EthernetSignals::ClientSignal::Signals::TableSignal::TryBeat
              << pairID
              << cardSuit
              << cardDignity;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}
void ServerConnector::instanceSlotPlayerTryToss(Card::Suit cardSuit, Card::Dignity cardDignity)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppInstToServInst
              << EthernetSignals::ClientSignal::Signals::TableSignal::TryToss
              << cardSuit
              << cardDignity;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}
void ServerConnector::instanceSlotTryTransferable(Card::Suit cardSuit, Card::Dignity cardDignity)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppInstToServInst
              << EthernetSignals::ClientSignal::Signals::TableSignal::TryTransferable
              << cardSuit
              << cardDignity;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}



void ServerConnector::registrationSlotPlayerLogIn(const QString& name, const QString& password)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::SignInSignals
              << EthernetSignals::ClientSignal::Signals::SignIn::TryLogIn
              << name
              << password;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}
void ServerConnector::registrationSlotPlayerRegistration(const QString& name, const QString& password)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::SignInSignals
              << EthernetSignals::ClientSignal::Signals::SignIn::TryRegistration
              << name
              << password;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}
void ServerConnector::registrationSlotPlayerLogOut()
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::SignInSignals
              << EthernetSignals::ClientSignal::Signals::SignIn::LogOut;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}


void ServerConnector::applicationSlotPlayerWantPlay(SettingsStruct settings)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::PlayerWantPlay
              << settings.m_deckType
              << settings.m_countOfPlayers
              << settings.m_trancferableAbility
              << settings.m_rateIndex;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}
void ServerConnector::applicationSlotPlayerExitFromWaitingRoom()
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::PlayerExitFromWaitingRoom;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}

void ServerConnector::financeSlotPlayerDepositWallet(Cash sum)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::PlayerDepositMoney
              << sum;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}
void ServerConnector::financeSlotPlayerWithdrawWallet(Cash sum)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::PlayerWithdrawMoney
              << sum;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}



void ServerConnector::messageSlotSendMessage(Canal canal, const QString& message)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::MessageSignal
              << canal
              << message;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}

void ServerConnector::serverSlotReadyRead(const QByteArray& dataBlock)
{
    QDataStream inStream(dataBlock);
    EthernetSignals::ServerSignal::TypeSignal typeSignal;
    inStream >> typeSignal;
    switch (typeSignal)
    {
        case EthernetSignals::ServerSignal::TypeSignal::FromServToApp:
        {
            this->serverSlotReadFromServToApp(inStream);
            break;
        }
        case EthernetSignals::ServerSignal::TypeSignal::FromServInstToAppInst:
        {
            this->serverSlotReadFromServInstToAppInst(inStream);
            break;
        }
        case EthernetSignals::ServerSignal::TypeSignal::SignInSignals:
        {
            this->serverSlotReadSignIn(inStream);
            break;
        }
    }
}
void ServerConnector::serverSlotReadSignIn(QDataStream& inStream)
{
    EthernetSignals::ServerSignal::Signals::SignIn typeMessage;
    inStream >> typeMessage;
    switch(typeMessage)
    {
        case EthernetSignals::ServerSignal::Signals::SignIn::SuccesfullySignIn          :
        {
            QString name;
            Cash dollars;
            Cash tokens;
            quint32 countOfGames;
            quint32 raitingPoints;
            QPixmap userAvatar;
            inStream >> m_ID >> name >> dollars >> tokens >> countOfGames >> raitingPoints >> userAvatar;
            emit this->registrationSignalSuccusfullySignIn(m_ID, name, dollars, tokens, countOfGames, raitingPoints, userAvatar);
            break;
        }
        case EthernetSignals::ServerSignal::Signals::SignIn::UnsuccesfullySignIn        :
        {
            QString errorMessage;
            inStream >> errorMessage;
            emit this->registrationSignalUnsuccusfullySignIn(errorMessage);
            break;
        }
        case EthernetSignals::ServerSignal::Signals::SignIn::LogOut                     :
        {
            emit this->registrationSignalConfirmLogOut();
            break;
        }
    }
}
void ServerConnector::serverSlotReadFromServToApp(QDataStream& inStream)
{
    EthernetSignals::ServerSignal::Signals::ServerSignal typeMessage;
    inStream >> typeMessage;
    switch(typeMessage)
    {
        case EthernetSignals::ServerSignal::Signals::ServerSignal::YouAreAddedToTheQueue      :
        {
            emit this->queueSignalUserAddedToWaitingRoom();
            break;
        }
        case EthernetSignals::ServerSignal::Signals::ServerSignal::YouAreRemovedFromTheQueue  :
        {
            emit this->queueSignalUserRemovedFromWaitingRoom();
            break;
        }
        case EthernetSignals::ServerSignal::Signals::ServerSignal::GetAllPlayInstanceOptions  :
        {
            Card::Suit trumpS;
            Card::Dignity trumpD;
            inStream >> trumpS >> trumpD;

            quint8 amountOfPlayers;


            inStream >> amountOfPlayers;
            QList<GameUserInformation*> allPlayers;
            for(quint8 i = 0; i < amountOfPlayers; ++i)
            {
                UserID id;
                QString name;
                QPixmap userAvatar;
                inStream >> id >> name >> userAvatar;
                allPlayers.push_back(new GameUserInformation(id, name, userAvatar));
            }


            UserID attacker;
            UserID defender;
            DeckSize sizeOfDeck;
            inStream >> attacker >> defender >> sizeOfDeck;
            emit signalApplicationCreateGameInstance(trumpS, trumpD, this->m_ID, allPlayers, attacker, defender, sizeOfDeck);

            break;
        }
        case EthernetSignals::ServerSignal::Signals::ServerSignal::AlertMessage               :
        {
            QString title;
            QString message;
            inStream >> title >> message;
            emit this->signalApplicationMakeAlert(title, message);

            break;
        }

        case EthernetSignals::ServerSignal::Signals::ServerSignal::UserMessageSignal         :
        {
            UserID id;
            QString name;
            Canal canal;
            QString message;
            inStream >> id >> name >> canal >> message;
            if(id == this->m_ID)
            {
                emit this->messageSignalReceiveUserMessage(canal, id, QString("Me: %1").arg(message));
            }
            else
            {
                emit this->messageSignalReceiveUserMessage(canal, id, QString("[%1]: %2").arg(name).arg(message));
            }
            break;
        }
        case EthernetSignals::ServerSignal::Signals::ServerSignal::ServerMessageSignal       :
        {
            QString message;
            inStream >> message;

            emit this->messageSignalReceiveServerMessage(QString("Server: %1").arg(message));
            break;
        }
        case EthernetSignals::ServerSignal::Signals::ServerSignal::UpdateUserInformation   :
        {
            QString name;
            Cash dollars;
            Cash tokens;
            quint32 countOfGames;
            quint32 raitingPoints;
            inStream >> name >> dollars >> tokens >> countOfGames >> raitingPoints;

            emit this->signalUpdateThisUserFullInformation(name, dollars, tokens, countOfGames, raitingPoints);
            break;
        }
    }
}
void ServerConnector::serverSlotReadFromServInstToAppInst(QDataStream& inStream)
{
    EthernetSignals::ServerSignal::Signals::InstanceSignal typeMessage;
    inStream >> typeMessage;
    switch (typeMessage)
    {
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::PlayerTakeAllCards              :
        {
            UserID playerID;
            UserID attackerID;
            UserID defenderID;
            inStream >> playerID >> attackerID >> defenderID;
            emit this->signalInstancePlayerTakeAllCards(playerID);
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::PlayerTossedCard                :
        {
            UserID playerID;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            inStream >> playerID >> cardSuit >> cardDignity;
            emit this->signalInstancePlayerTossedCard(playerID, cardSuit, cardDignity);

            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::PlayerBeatCard                  :
        {
            UserID playerID;
            PairID pairID;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            inStream >> playerID >> pairID >> cardSuit >> cardDignity;
            emit this->signalInstancePlayerBeatCard(playerID, pairID, cardSuit, cardDignity);

            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::PlayerTrancferable              :
        {
            UserID playerID;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            UserID attackerID;
            UserID defenderID;
            inStream >> playerID >> cardSuit >> cardDignity >> attackerID >> defenderID;
            emit this->signalInstancePlayerTransferable(playerID, cardSuit, cardDignity);
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::ThisPlayerTakeCardFromDeck      :
        {
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            inStream >> cardSuit >> cardDignity;
            emit this->signalInstanceThisPlayerTakeCardFromDeck(cardSuit, cardDignity);

            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::OtherPlayerTakeCardFromDeck     :
        {
            UserID playerID;
            inStream >> playerID;
            emit this->signalInstanceOtherPlayerTakeCardFromDeck(playerID);

            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::MakeTurn                        :
        {
            UserID attackerID;
            UserID defenderID;
            inStream >> attackerID >> defenderID;
            emit this->signalInstanceMakeTurn();
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::UnsuccesfullyAction:
        {
            emit this->signalInstanceUnsuccesfullyAction();
            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::EndOfMatch                      :
        {
            QList<GameUserInformation*> m_winnersList;
            quint8 m_amountOfPlayers;
            inStream >> m_amountOfPlayers;
            for(quint8 i = 0; i < m_amountOfPlayers; ++i)
            {
                UserID playerID;
                QString playerName;
                inStream >> playerID >> playerName;
                m_winnersList.push_back(new GameUserInformation(playerID, playerName, QPixmap()));
            }
            emit this->signalInstanceEndOfMatch(m_winnersList);
            break;
        }
    }
}


void ServerConnector::serverSlotError(QAbstractSocket::SocketError err)
{
    switch(err)
    {
        case QAbstractSocket::SocketError::HostNotFoundError      : { qDebug() << ("Invalid ip address"); break; }
        case QAbstractSocket::SocketError::RemoteHostClosedError  : { qDebug() << ("Server was closed"); break; }
        case QAbstractSocket::SocketError::ConnectionRefusedError : { qDebug() << ("Unable to connect to server"); break; }
        default: { qDebug() << ("Undefined error"); break; }
    }
}
void ServerConnector::serverSlotConnected()
{
    qDebug() << ("Succesfully connecting with server");
}






void ServerConnector::slotUpdateUserAvatar(const QPixmap& newAvatar)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::UpdateUserAvatar
              << newAvatar;

    this->m_webSocket->sendBinaryMessage(dataBlock);
}

