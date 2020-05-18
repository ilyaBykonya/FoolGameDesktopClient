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
        QObject::connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ApplicationEthernetController::serverSlotReadyRead);
    }

void ApplicationEthernetController::instanceSlotActionButtonWasClicked()
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0) << SignalFromApplicationOnServer::ActionButtonWasClicked;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}
void ApplicationEthernetController::instanceSlotPlayerTryBeat(Card* card, qint16 pairID)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << SignalFromApplicationOnServer::TryBeat
              << card->suit()
              << card->dignity()
              << pairID;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}

void ApplicationEthernetController::instanceSlotPlayerTryToss(Card* card)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << SignalFromApplicationOnServer::TryToss
              << card->suit()
              << card->dignity();
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
}

void ApplicationEthernetController::instanceSlotPlayerWantPlay()
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0) << SignalFromApplicationOnServer::PlayerWantPlay;
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
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

        SignalFromServerToApplication signalType;
        //считываем тип сообщения
        //дальче обрабатывать через switch
        //для перечисления SignalFromServerToApplication
        dataBlock >> signalType;
        switch(signalType)
        {
            case SignalFromServerToApplication::PlayerTakeAllCards                :
            {
                qDebug() << ("PlayerTakeAllCards");
                qint16 playerID;
                dataBlock >> playerID;
                emit this->signalPlayerTakeAllCards(playerID);
                break;
            }
            case SignalFromServerToApplication::PlayerTossedCard            :
            {
                qDebug() << ("PlayerTossedCard");
                qint16 playerID;
                Card::Suit suit;
                Card::Dignity dignity;
                dataBlock >> playerID >> suit >> dignity;
                emit this->signalPlayerTossedCard(playerID, suit, dignity);
                break;
            }
            case SignalFromServerToApplication::PlayerBeatCard              :
            {
                qDebug() << ("PlayerBeatCard");
                qint16 playerID;
                qint16 battlePairID;
                Card::Suit suit;
                Card::Dignity dignity;
                dataBlock >> playerID >> battlePairID >> suit >> dignity;
                qDebug() << QString("Player[%1] beat. Card[%2:%3]. Pair[%4]").arg(playerID).arg(suit).arg(dignity).arg(battlePairID);
                emit this->signalPlayerBeatCard(playerID, battlePairID, suit, dignity);
                break;
            }
            case ThisPlayerTakeCardFromDeck                                 :
            {
                 qDebug() << ("ThisPlayerTakeCardFromDeck");
                 Card::Suit s;
                 Card::Dignity d;
                 dataBlock >> s >> d;
                 emit signalThisPlayerTakeCardFromDeck(s, d);
                 break;
            }
            case OtherPlayerTakeCardFromDeck:
            {
                qDebug() << ("OtherPlayerTakeCardFromDeck");
                qint16 id;
                dataBlock >> id;

                emit signalOtherPlayerTakeCardFromDeck(id);
                break;
            }
            case SetNewMainPlayersPair:
            {
                qDebug() << ("SetNewMainPlayersPair");
                qint16 attackerGlobalID;
                qint16 defenderGlobalID;
                dataBlock >> attackerGlobalID >> defenderGlobalID;
                emit this->signalSetNewMainPair(attackerGlobalID, defenderGlobalID);
                break;
            }
            case SignalFromServerToApplication::MakeTurn                    :
            {
                qDebug() << ("MakeTurn");
                emit this->signalMakeTurn();
                break;
            }
            case YourActionIsUnsuccesfully:
            {
                qDebug() << ("Action unsuccesfull");
                emit this->signalYourActionIsUnsuccesfully();
                break;
            }


            case SignalFromServerToApplication::SetPlayerID                 :
            {
                qDebug() << ("SetPlayerID");
                dataBlock >> this->m_ID;

                break;
            }
            case SignalFromServerToApplication::GetAllPlayInstanceOptions   :
            {

                qDebug() << "GetAllPlayInstanceOptions";
                Card::Suit trumpS;
                Card::Dignity trumpD;
                dataBlock >> trumpS >> trumpD;
                qint16 amountOfPlayers;
                dataBlock >> amountOfPlayers;
                qDebug() << "Amount of players: " << amountOfPlayers << "\nPlayers ID:";
                QList<qint16> allPlayersID;
                for(int i = 0; i < amountOfPlayers; ++i)
                {
                    qint16 playerID;
                    dataBlock >> playerID;
                    allPlayersID.push_back(playerID);
                    qDebug() << "\t" << playerID;
                }


                qint16 attacker;
                qint16 defender;
                dataBlock >> attacker >> defender;
                qDebug() << "Main pair: " << attacker << "\t" << defender;
                emit signalCreateGameInstance(trumpS, trumpD, this->m_ID, allPlayersID, attacker, defender);
                break;
            }
        }

        m_nextDataBlockSize = 0;
    }
}
