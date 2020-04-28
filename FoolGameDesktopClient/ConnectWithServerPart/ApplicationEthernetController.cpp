#include "ApplicationEthernetController.h"

ApplicationEthernetController::ApplicationEthernetController(QWidget* parent)
    :QWidget{ parent },
     m_tcpSocket{ new QTcpSocket(this) },
     m_textEdit{ new QTextEdit(this) },
     m_nextDataBlockSize{ 0 },
     m_startGame{ new QPushButton("Start game", this) }
    {
        m_textEdit->setReadOnly(true);
        //"locathos" - имя хоста (равносильно ip). Будет считываться из файла
        //2323 - номер сокета. Будет считываться из файла
        m_tcpSocket->connectToHost("localhost", 2323);
        QObject::connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ApplicationEthernetController::serverSlotReadyRead);
        QObject::connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(serverSlotError(QAbstractSocket::SocketError)));
        QObject::connect(m_tcpSocket, &QTcpSocket::readyRead, this, &ApplicationEthernetController::serverSlotReadyRead);

        QObject::connect(m_startGame, &QPushButton::clicked, this, &ApplicationEthernetController::instanceSlotPlayerWantPlay);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(new QLabel("<center><b><i>Client controller</i></b></center>"));
        layout->addWidget(m_textEdit);
        layout->addWidget(m_startGame);
        this->setLayout(layout);


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
    m_textEdit->append("Action button was clicked");
}
void ApplicationEthernetController::instanceSlotPlayerTryBeat(Card* card, BattlePairWidget* pair)
{
    QByteArray dataBlock;
    QDataStream outStream(&dataBlock, QIODevice::OpenModeFlag::WriteOnly);
    outStream.setVersion(QDataStream::Version::Qt_5_14);
    outStream << qint16(0)
              << SignalFromApplicationOnServer::TryBeat
              << card->suit()
              << card->dignity()
              << pair->id();
    outStream.device()->seek(0);
    outStream << qint16(dataBlock.size() - sizeof(qint16));
    m_tcpSocket->write(dataBlock);
    m_textEdit->append(QString("Player successfully beat card [%1:%2] with pair [%3]").arg(card->suit()).arg(card->dignity()).arg(pair->id()));
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
    m_textEdit->append(QString("Player successfully toss card [%1:%2]").arg(card->suit()).arg(card->dignity()));
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
    m_textEdit->append("Request to make play");
}


void ApplicationEthernetController::serverSlotError(QAbstractSocket::SocketError err)
{
    switch(err)
    {
        case QAbstractSocket::SocketError::HostNotFoundError      : { m_textEdit->append("Invalid ip address"); break; }
        case QAbstractSocket::SocketError::RemoteHostClosedError  : { m_textEdit->append("Server was closed"); break; }
        case QAbstractSocket::SocketError::ConnectionRefusedError : { m_textEdit->append("Unable to connect to server"); break; }
        default: { m_textEdit->append("Undefined error"); break; }
    }
}
void ApplicationEthernetController::serverSlotConnected()
{
    m_textEdit->append("Succesfully connecting with server");
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
                this->m_textEdit->append("PlayerTakeAllCards");
                qint16 playerID;
                dataBlock >> playerID;
                emit this->signalPlayerTakeAllCards(playerID);
                break;
            }
            case SignalFromServerToApplication::PlayerTossedCard            :
            {
                this->m_textEdit->append("PlayerTossedCard");
                qint16 playerID;
                Card::Suit suit;
                Card::Dignity dignity;
                dataBlock >> playerID >> suit >> dignity;
                emit this->signalPlayerTossedCard(playerID, suit, dignity);
                break;
            }
            case SignalFromServerToApplication::PlayerBeatCard              :
            {
                this->m_textEdit->append("PlayerBeatCard");
                qint16 playerID;
                qint16 battlePairID;
                Card::Suit suit;
                Card::Dignity dignity;
                dataBlock >> playerID >> battlePairID >> suit >> dignity;
                emit this->signalPlayerBeatCard(playerID, battlePairID, suit, dignity);
                break;
            }
            case SignalFromServerToApplication::TakeCardFromDeck                   :
            {
                this->m_textEdit->append("TakeCardFromDeck");
                qint16 playerID;
                Card::Suit suit;
                Card::Dignity dignity;
                dataBlock >> playerID >> suit >> dignity;
                emit this->signalTakeCardFromDeck(playerID, suit, dignity);
                break;
            }
            case SetNewMainPlayersPair:
            {
                this->m_textEdit->append("SetNewMainPlayersPair");
                qint16 attaclerGlobalID;
                qint16 defenderGlobalID;
                dataBlock >> attaclerGlobalID >> defenderGlobalID;
                emit this->signalSetNewMainPair(attaclerGlobalID, defenderGlobalID);
                break;
            }
            case SignalFromServerToApplication::MakeTurn                           :
            {
                this->m_textEdit->append("MakeTurn");
                emit this->signalMakeTurn();
                break;
            }

            case SignalFromServerToApplication::SetPlayerID                        :
            {
                this->m_textEdit->append("SetPlayerID");
                dataBlock >> this->m_ID;
                //*******************************************************************************************************
                //TEST
                m_tableWidget = new GameTableWidget(this->m_ID, {this->m_ID, 2, 3}, this->m_ID, 2, nullptr);
                QObject::connect(this, &ApplicationEthernetController::signalPlayerTakeAllCards, m_tableWidget, &GameTableWidget::serverSlotPlayerTakeAllCards);
                QObject::connect(this, &ApplicationEthernetController::signalMakeTurn, m_tableWidget, &GameTableWidget::serverSlotMakeTurn);
                QObject::connect(this, &ApplicationEthernetController::signalSetNewMainPair, m_tableWidget, &GameTableWidget::serverSlotSetNewMainPair);
                QObject::connect(this, &ApplicationEthernetController::signalPlayerTossedCard, m_tableWidget, &GameTableWidget::serverSlotPlayerTossedCard);
                QObject::connect(this, &ApplicationEthernetController::signalPlayerBeatCard, m_tableWidget, &GameTableWidget::serverSlotPlayerBeatCard);
                QObject::connect(this, &ApplicationEthernetController::signalTakeCardFromDeck, m_tableWidget, &GameTableWidget::serverSlotPlayerTakeCardFromDeck);

                QObject::connect(m_tableWidget, &GameTableWidget::tryBeat, this, &ApplicationEthernetController::instanceSlotPlayerTryBeat);
                QObject::connect(m_tableWidget, &GameTableWidget::tryToss, this, &ApplicationEthernetController::instanceSlotPlayerTryToss);
                QObject::connect(m_tableWidget, &GameTableWidget::actionButtonWasClicked, this, &ApplicationEthernetController::instanceSlotActionButtonWasClicked);

                m_tableWidget->show();
                //*******************************************************************************************************
                break;
            }
            case SignalFromServerToApplication::GetAllPlayInstanceOptions          :
            {
                this->m_textEdit->append("GetAllPlayInstanceOptions");
                qint16 amountOfOtherPlayers;
                dataBlock >> amountOfOtherPlayers;
                QList<qint16> allPlayersID;
                for(int i = 0; i < amountOfOtherPlayers; ++i)
                {
                    qint16 playerID;
                    dataBlock >> playerID;
                    allPlayersID.push_back(playerID);
                }


                qint16 attacker;
                qint16 defender;
                dataBlock >> attacker >> defender;

                m_tableWidget = new GameTableWidget(this->m_ID, allPlayersID, attacker, defender, nullptr);
                QObject::connect(this, &ApplicationEthernetController::signalPlayerTakeAllCards, m_tableWidget, &GameTableWidget::serverSlotPlayerTakeAllCards);
                QObject::connect(this, &ApplicationEthernetController::signalMakeTurn, m_tableWidget, &GameTableWidget::serverSlotMakeTurn);
                QObject::connect(this, &ApplicationEthernetController::signalSetNewMainPair, m_tableWidget, &GameTableWidget::serverSlotSetNewMainPair);
                QObject::connect(this, &ApplicationEthernetController::signalPlayerTossedCard, m_tableWidget, &GameTableWidget::serverSlotPlayerTossedCard);
                QObject::connect(this, &ApplicationEthernetController::signalPlayerBeatCard, m_tableWidget, &GameTableWidget::serverSlotPlayerBeatCard);
                QObject::connect(this, &ApplicationEthernetController::signalTakeCardFromDeck, m_tableWidget, &GameTableWidget::serverSlotPlayerTakeCardFromDeck);

                QObject::connect(m_tableWidget, &GameTableWidget::tryBeat, this, &ApplicationEthernetController::instanceSlotPlayerTryBeat);
                QObject::connect(m_tableWidget, &GameTableWidget::tryToss, this, &ApplicationEthernetController::instanceSlotPlayerTryToss);
                QObject::connect(m_tableWidget, &GameTableWidget::actionButtonWasClicked, this, &ApplicationEthernetController::instanceSlotActionButtonWasClicked);

                break;
            }
        }

        m_nextDataBlockSize = 0;
    }
}
