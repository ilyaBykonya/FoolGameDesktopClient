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
    qDebug() << QString("EMIT ACTION BUTTON WAS CLICKED");
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
    qDebug() << QString("EMIT TRY BEAT [%1:%2]->[%3]").arg(cardSuit).arg(cardDignity).arg(pairID);
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
    qDebug() << QString("EMIT TRY TOSS [%1:%2]").arg(cardSuit).arg(cardDignity);
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
    qDebug() << QString("EMIT TRY TRANCFERABLE [%1:%2]").arg(cardSuit).arg(cardDignity);
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
    qDebug() << QString("EMIT PLAYER REGISTRATION [%1:%2]").arg(name).arg(password);
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
    qDebug() << QString("EMIT PLAYER REGISTRATION [%1:%2]").arg(name).arg(password);
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

void ApplicationEthernetController::applicationSlotPlayerWantPlay(quint8 deckTypeFlags, quint8 playersCountFlags, bool realCash)
{
    qDebug() << QString("EMIT PLAYER WANT PLAY [%1:%2:3]").arg(deckTypeFlags).arg(playersCountFlags).arg(realCash);
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << EthernetSignals::ClientSignal::TypeSignal::FromAppToServ
              << EthernetSignals::ClientSignal::ApplicationSignal::PlayerWantPlay
              << deckTypeFlags
              << playersCountFlags
              << realCash;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::applicationSlotPlayerDepositMoney(qint16 sum)
{
    qDebug() << QString("EMIT PLAYER DEPOSIT [%1]").arg(sum);
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
    qDebug() << QString("EMIT PLAYER WITHDRAW [%1]").arg(sum);
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
        qDebug() << "Read data block: " << typeSignal;
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
            qDebug() << QString("READ THIS_PLAYER_ID [%1]").arg(id);
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
            qDebug() << QString("READ GAME_TABLE_OPTIONS [%1:%2:%3:%4:%5]").arg(trumpS).arg(trumpD).arg(attacker).arg(defender).arg(sizeOfDeck);
            emit signalApplicationCreateGameInstance(trumpS, trumpD, this->m_ID, allPlayersID, attacker, defender, sizeOfDeck);

            break;
        }
        case EthernetSignals::ServerSignal::ServerSignal::AlertMessage               :
        {
            QString title;
            QString message;
            dataBlock >> title >> message;
            qDebug() << QString("READ ALERT MESSAGE [%1::%2]").arg(title).arg(message);
            emit this->signalApplicationMakeAlert(title, message);

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
            qDebug() << QString("READ PLAYER_TAKE_ALL_CARDS [%1]").arg(playerID);
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
            qDebug() << QString("READ PLAYER_TOSS [%1]->[%2:%3]").arg(playerID).arg(cardSuit).arg(cardDignity);
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
            qDebug() << QString("READ PLAYER_BEAT [%1]->[%2]->[%3:%4]").arg(playerID).arg(pairID).arg(cardSuit).arg(cardDignity);
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
            qDebug() << QString("READ PLAYER_TRANCFERABLE [%1]->[%2:%3]").arg(playerID).arg(cardSuit).arg(cardDignity);
            emit this->signalInstancePlayerTransferable(playerID, cardSuit, cardDignity);
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::ThisPlayerTakeCardFromDeck      :
        {
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            dataBlock >> cardSuit >> cardDignity;
            qDebug() << QString("READ THIS_PLAYER_TAKE_CARD [%1:%2]").arg(cardSuit).arg(cardDignity);
            emit this->signalInstanceThisPlayerTakeCardFromDeck(cardSuit, cardDignity);

            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::OtherPlayerTakeCardFromDeck     :
        {
            qint16 playerID;
            dataBlock >> playerID;
            qDebug() << QString("READ OTHER_PLAYER_TAKE_CARD [%1]").arg(playerID);
            emit this->signalInstanceOtherPlayerTakeCardFromDeck(playerID);

            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::MakeTurn                        :
        {
            qDebug() << QString("READ MAKE_TURN");
            qint16 attackerID;
            qint16 defenderID;
            dataBlock >> attackerID >> defenderID;
            emit this->signalInstanceMakeTurn();
            emit this->signalInstanceSetNewMainPair(attackerID, defenderID);
            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::UnsuccesfullyAction:
        {
            qDebug() << QString("READ UNSUCCESFULLY_TOSS");
            PlayerActionType actionType;
            Card::Suit cardSuit;
            Card::Dignity cardDignity;
            qint16 pairID;
            dataBlock >> actionType
                      >> cardSuit
                      >> cardDignity
                      >> pairID;
            emit this->signalInstanceUnsuccesfullyAction(actionType, cardSuit, cardDignity, pairID);
            break;
        }
        case EthernetSignals::ServerSignal::InstanceSignal::EndOfMatch                      :
        {
            qint16 wonMoney;
            dataBlock >> wonMoney;
            qDebug() << QString("READ END_MATCH [%1]").arg(wonMoney);
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
