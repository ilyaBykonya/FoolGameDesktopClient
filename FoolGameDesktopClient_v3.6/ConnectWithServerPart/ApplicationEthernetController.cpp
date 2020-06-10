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
              << EthernetSignals::ClientSignal::TableSignal::ActionButtonWasClicked;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::instanceSlotPlayerTryBeat(Card::Suit cardSuit, Card::Dignity cardDignity, qint16 pairID)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppInstToServInst
              << EthernetSignals::ClientSignal::TableSignal::TryBeat
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
              << EthernetSignals::ClientSignal::TableSignal::TryToss
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
              << EthernetSignals::ClientSignal::TableSignal::TryTransferable
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
              << EthernetSignals::ClientSignal::SignIn::TryLogIn
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
              << EthernetSignals::ClientSignal::SignIn::TryRegistration
              << name
              << password;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}

void ApplicationEthernetController::applicationSlotPlayerWantPlay(quint8 deckTypeFlags, quint8 playersCountFlags, bool trancferableAbility)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::ApplicationSignal::PlayerWantPlay
              << deckTypeFlags
              << playersCountFlags
              << trancferableAbility;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::applicationSlotPlayerDepositMoney(qint16 sum)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::ApplicationSignal::PlayerDepositMoney
              << sum;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::applicationSlotPlayerWithdrawMoney(qint16 sum)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::ApplicationSignal::PlayerWithdrawMoney
              << sum;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}

void ApplicationEthernetController::messageSlotSendMessage(ChatWindow::Canal canal, const QString& message)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::ApplicationSignal::MessageSignal
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
    EthernetSignals::ServerSignal::SignIn typeMessage;
    dataBlock >> typeMessage;
    switch(typeMessage)
    {
        case EthernetSignals::ServerSignal::SignIn::SuccesfullyLogIn                :
        {
            emit this->registrationSignalSuccusfullyLogIn();
            break;
        }
        case EthernetSignals::ServerSignal::SignIn::UnsuccesfullyLogIn              :
        {
            QString errorMessage;
            dataBlock >> errorMessage;
            emit this->registrationSignalUnsuccusfullyLogIn(errorMessage);
            break;
        }
        case EthernetSignals::ServerSignal::SignIn::SuccesfullyRegistration         :
        {
            emit this->registrationSignalSuccusfullyRegistration();
            break;
        }
        case EthernetSignals::ServerSignal::SignIn::UnsuccesfullyRegistration       :
        {
            QString errorMessage;
            dataBlock >> errorMessage;
            emit this->registrationSignalUnsuccusfullyRegistration(errorMessage);
            break;
        }
    }
}
void ApplicationEthernetController::serverSlotReadFromServToApp(QDataStream& dataBlock)
{
    EthernetSignals::ServerSignal::ServerSignal typeMessage;
    dataBlock >> typeMessage;
    switch(typeMessage)
    {
        case EthernetSignals::ServerSignal::ServerSignal::SetPlayerID                :
        {
            qint16 id;
            dataBlock >> id;
            m_ID = id;
            break;
        }
        case EthernetSignals::ServerSignal::ServerSignal::GetAllPlayInstanceOptions  :
        {
            Card::Suit trumpS;
            Card::Dignity trumpD;
            dataBlock >> trumpS >> trumpD;

            qint16 amountOfPlayers;


            dataBlock >> amountOfPlayers;
            QList<qint16> allPlayersID;
            for(int i = 0; i < amountOfPlayers; ++i)
            {
                qint16 playerID;
                dataBlock >> playerID;
                allPlayersID.push_back(playerID);
            }


            qint16 attacker;
            qint16 defender;
            qint16 sizeOfDeck;
            dataBlock >> attacker >> defender >> sizeOfDeck;
            emit signalApplicationCreateGameInstance(trumpS, trumpD, this->m_ID, allPlayersID, attacker, defender, sizeOfDeck);

            break;
        }
        case EthernetSignals::ServerSignal::ServerSignal::AlertMessage               :
        {
            QString title;
            QString message;
            dataBlock >> title >> message;
            emit this->signalApplicationMakeAlert(title, message);

            break;
        }
        case EthernetSignals::ServerSignal::ServerSignal::MessageSignal               :
        {
            quint16 userID;
            ChatWindow::Canal canal;
            QString message;
            dataBlock >> userID >> canal >> message;
            if(userID == m_ID)
            {
                emit this->messageSignalReceiveMessage(canal, QString("Me: %1").arg(message));
            }
            else
            {
                emit this->messageSignalReceiveMessage(canal, QString("User [%1] send: %2").arg(userID).arg(message));
            }

            break;
        }
    }
}
void ApplicationEthernetController::serverSlotReadFromServInstToAppInst(QDataStream& dataBlock)
{
    EthernetSignals::ServerSignal::InstanceSignal typeMessage;
    dataBlock >> typeMessage;
    switch (typeMessage)
    {
        case EthernetSignals::ServerSignal::InstanceSignal::PlayerTakeAllCards              :
        {
            qint16 playerID;
            qint16 attackerID;
            qint16 defenderID;
            dataBlock >> playerID >> attackerID >> defenderID;
            emit this->signalInstancePlayerTakeAllCards(playerID);
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::PlayerTossedCard                :
        {
            qint16 playerID;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            dataBlock >> playerID >> cardSuit >> cardDignity;
            emit this->signalInstancePlayerTossedCard(playerID, cardSuit, cardDignity);

            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::PlayerBeatCard                  :
        {
            qint16 playerID;
            qint16 pairID;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            dataBlock >> playerID >> pairID >> cardSuit >> cardDignity;
            emit this->signalInstancePlayerBeatCard(playerID, pairID, cardSuit, cardDignity);

            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::PlayerTrancferable              :
        {
            qint16 playerID;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            qint16 attackerID;
            qint16 defenderID;
            dataBlock >> playerID >> cardSuit >> cardDignity >> attackerID >> defenderID;
            emit this->signalInstancePlayerTransferable(playerID, cardSuit, cardDignity);
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::ThisPlayerTakeCardFromDeck      :
        {
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            dataBlock >> cardSuit >> cardDignity;
            emit this->signalInstanceThisPlayerTakeCardFromDeck(cardSuit, cardDignity);

            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::OtherPlayerTakeCardFromDeck     :
        {
            qint16 playerID;
            dataBlock >> playerID;
            emit this->signalInstanceOtherPlayerTakeCardFromDeck(playerID);

            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::MakeTurn                        :
        {
            qint16 attackerID;
            qint16 defenderID;
            dataBlock >> attackerID >> defenderID;
            emit this->signalInstanceMakeTurn();
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::UnsuccesfullyAction:
        {
            PlayerActionType actionType;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            qint16 pairID;
            dataBlock >> actionType
                      >> cardSuit
                      >> cardDignity
                      >> pairID;
            emit this->signalInstanceUnsuccesfullyAction(cardSuit, cardDignity, pairID);
            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::EndOfMatch                      :
        {
            qint16 wonMoney;
            dataBlock >> wonMoney;
            emit this->signalInstanceEndOfMatch();

            QString title = (wonMoney > 0) ? ("Yout win!") : ("You lose");
            QString sum = QString::number(wonMoney) + "$";
            emit this->signalApplicationMakeAlert(title, sum);
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
