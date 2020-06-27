#include "ApplicationEthernetController.h"

ApplicationEthernetController::ApplicationEthernetController(QObject* parent)
    :QObject{ parent },
     m_tcpSocket{ new QTcpSocket(this) },
     m_nextDataBlockSize{ 0 }
    {
        //"locathos" - имя хоста (равносильно ip). Будет считываться из файла
        //2323 - номер сокета. Будет считываться из файла
        m_tcpSocket->connectToHost("localhost", 2323);
        QObject::connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ApplicationEthernetController::serverSlotReadyRead);
        QObject::connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(serverSlotError(QAbstractSocket::SocketError)));
    }

void ApplicationEthernetController::instanceSlotActionButtonWasClicked()
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppInstToServInst
              << EthernetSignals::ClientSignal::Signals::TableSignal::ActionButtonWasClicked;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::instanceSlotPlayerTryBeat(PairID pairID, Card::Suit cardSuit, Card::Dignity cardDignity)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppInstToServInst
              << EthernetSignals::ClientSignal::Signals::TableSignal::TryBeat
              << pairID
              << cardSuit
              << cardDignity;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::instanceSlotPlayerTryToss(Card::Suit cardSuit, Card::Dignity cardDignity)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppInstToServInst
              << EthernetSignals::ClientSignal::Signals::TableSignal::TryToss
              << cardSuit
              << cardDignity;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::instanceSlotTryTransferable(Card::Suit cardSuit, Card::Dignity cardDignity)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppInstToServInst
              << EthernetSignals::ClientSignal::Signals::TableSignal::TryTransferable
              << cardSuit
              << cardDignity;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}



void ApplicationEthernetController::registrationSlotPlayerLogIn(const QString& name, const QString& password)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::SignInSignals
              << EthernetSignals::ClientSignal::Signals::SignIn::TryLogIn
              << name
              << password;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::registrationSlotPlayerRegistration(const QString& name, const QString& password)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::SignInSignals
              << EthernetSignals::ClientSignal::Signals::SignIn::TryRegistration
              << name
              << password;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::registrationSlotPlayerLogOut()
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::SignInSignals
              << EthernetSignals::ClientSignal::Signals::SignIn::LogOut;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}


void ApplicationEthernetController::applicationSlotPlayerWantPlay(SettingsStruct settings)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::PlayerWantPlay
              << settings.m_deckType
              << settings.m_countOfPlayers
              << settings.m_trancferableAbility;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::applicationSlotPlayerExitFromWaitingRoom()
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::PlayerExitFromWaitingRoom;

    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}

void ApplicationEthernetController::applicationSlotPlayerDepositMoney(Cash sum)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::PlayerDepositMoney
              << sum;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::applicationSlotPlayerWithdrawMoney(Cash sum)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::PlayerWithdrawMoney
              << sum;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}



void ApplicationEthernetController::messageSlotSendMessage(Canal canal, const QString& message)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::Signals::ApplicationSignal::MessageSignal
              << canal
              << message;

    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}

void ApplicationEthernetController::serverSlotReadyRead()
{
    QDataStream dataBlock(m_tcpSocket);

    for (;;)
    {
        if(!m_nextDataBlockSize)
        {
            if(m_tcpSocket->bytesAvailable() < sizeof(qint16))
                break;

            dataBlock >> m_nextDataBlockSize;
        }

        if(m_tcpSocket->bytesAvailable() < m_nextDataBlockSize)
                break;

        EthernetSignals::ServerSignal::TypeSignal typeSignal;
        dataBlock >> typeSignal;
        switch (typeSignal)
        {
            case EthernetSignals::ServerSignal::TypeSignal::FromServToApp:
            {
                this->serverSlotReadFromServToApp(dataBlock);
                break;
            }
            case EthernetSignals::ServerSignal::TypeSignal::FromServInstToAppInst:
            {
                this->serverSlotReadFromServInstToAppInst(dataBlock);
                break;
            }
            case EthernetSignals::ServerSignal::TypeSignal::SignInSignals:
            {
                this->serverSlotReadSignIn(dataBlock);
                break;
            }
        }
        m_nextDataBlockSize = 0;
    }
}
void ApplicationEthernetController::serverSlotReadSignIn(QDataStream& dataBlock)
{
    EthernetSignals::ServerSignal::Signals::SignIn typeMessage;
    dataBlock >> typeMessage;
    switch(typeMessage)
    {
        case EthernetSignals::ServerSignal::Signals::SignIn::SuccesfullySignIn          :
        {
            dataBlock >> m_ID;
            emit this->registrationSignalSuccusfullySignIn(m_ID);
            break;
        }
        case EthernetSignals::ServerSignal::Signals::SignIn::UnsuccesfullySignIn        :
        {
            QString errorMessage;
            dataBlock >> errorMessage;
            emit this->registrationSignalUnsuccusfullySignIn(errorMessage);
            break;
        }
        case EthernetSignals::ServerSignal::Signals::SignIn::LogOut                     :
        {
            emit this->registrationSignalConfirmlogOut();
            break;
        }
    }
}
void ApplicationEthernetController::serverSlotReadFromServToApp(QDataStream& dataBlock)
{
    EthernetSignals::ServerSignal::Signals::ServerSignal typeMessage;
    dataBlock >> typeMessage;
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
            dataBlock >> trumpS >> trumpD;

            quint8 amountOfPlayers;


            dataBlock >> amountOfPlayers;
            QList<UserInformation> allPlayers;
            for(quint8 i = 0; i < amountOfPlayers; ++i)
            {
                UserID id;
                QString name;
                dataBlock >> id >> name;
                allPlayers.push_back(UserInformation(id, name));
            }


            UserID attacker;
            UserID defender;
            quint8 sizeOfDeck;
            dataBlock >> attacker >> defender >> sizeOfDeck;
            emit signalApplicationCreateGameInstance(trumpS, trumpD, this->m_ID, allPlayers, attacker, defender, sizeOfDeck);

            break;
        }
        case EthernetSignals::ServerSignal::Signals::ServerSignal::AlertMessage               :
        {
            QString title;
            QString message;
            dataBlock >> title >> message;
            emit this->signalApplicationMakeAlert(title, message);

            break;
        }

        case EthernetSignals::ServerSignal::Signals::ServerSignal::UserMessageSignal         :
        {
            UserID id;
            QString name;
            Canal canal;
            QString message;
            dataBlock >> id >> name >> canal >> message;
            UserInformation user(id, name);
            if(user.userID() == this->m_ID)
            {
                emit this->messageSignalReceiveUserMessage(canal, user.userID() , QString("Me: %1").arg(message));
            }
            else
            {
                emit this->messageSignalReceiveUserMessage(canal, user.userID() , QString("[%1]: %2").arg(user.userName()).arg(message));
            }
            break;
        }
        case EthernetSignals::ServerSignal::Signals::ServerSignal::ServerMessageSignal       :
        {
            QString message;
            dataBlock >> message;

            emit this->messageSignalReceiveServerMessage(QString("Server: %1").arg(message));
            break;
        }
    }
}
void ApplicationEthernetController::serverSlotReadFromServInstToAppInst(QDataStream& dataBlock)
{
    EthernetSignals::ServerSignal::Signals::InstanceSignal typeMessage;
    dataBlock >> typeMessage;
    switch (typeMessage)
    {
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::PlayerTakeAllCards              :
        {
            UserID playerID;
            UserID attackerID;
            UserID defenderID;
            dataBlock >> playerID >> attackerID >> defenderID;
            emit this->signalInstancePlayerTakeAllCards(playerID);
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::PlayerTossedCard                :
        {
            UserID playerID;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            dataBlock >> playerID >> cardSuit >> cardDignity;
            emit this->signalInstancePlayerTossedCard(playerID, cardSuit, cardDignity);

            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::PlayerBeatCard                  :
        {
            UserID playerID;
            PairID pairID;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            dataBlock >> playerID >> pairID >> cardSuit >> cardDignity;
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
            dataBlock >> playerID >> cardSuit >> cardDignity >> attackerID >> defenderID;
            emit this->signalInstancePlayerTransferable(playerID, cardSuit, cardDignity);
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::ThisPlayerTakeCardFromDeck      :
        {
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            dataBlock >> cardSuit >> cardDignity;
            emit this->signalInstanceThisPlayerTakeCardFromDeck(cardSuit, cardDignity);

            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::OtherPlayerTakeCardFromDeck     :
        {
            UserID playerID;
            dataBlock >> playerID;
            emit this->signalInstanceOtherPlayerTakeCardFromDeck(playerID);

            break;
        }
        case EthernetSignals::ServerSignal::Signals::InstanceSignal::MakeTurn                        :
        {
            UserID attackerID;
            UserID defenderID;
            dataBlock >> attackerID >> defenderID;
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
            UserID wonPlayerID;
            dataBlock >> wonPlayerID;
            emit this->signalInstanceEndOfMatch(wonPlayerID);
            break;
        }
    }
}


void ApplicationEthernetController::serverSlotError(QAbstractSocket::SocketError err)
{
    switch(err)
    {
        case QAbstractSocket::SocketError::HostNotFoundError      : { qDebug() << ("Invalid ip address"); break; }
        case QAbstractSocket::SocketError::RemoteHostClosedError  : { qDebug() << ("Server was closed"); break; }
        case QAbstractSocket::SocketError::ConnectionRefusedError : { qDebug() << ("Unable to connect to server"); break; }
        default: { qDebug() << ("Undefined error"); break; }
    }
}
void ApplicationEthernetController::serverSlotConnected()
{
    qDebug() << ("Succesfully connecting with server");
}
