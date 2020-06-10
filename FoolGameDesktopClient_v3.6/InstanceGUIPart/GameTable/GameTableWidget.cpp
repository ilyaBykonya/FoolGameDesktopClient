#include "GameTableWidget.h"

GameTableWidget::GameTableWidget(Card::Suit trumpS,
                                 Card::Dignity trumpD,
                                 qint16 thisPlayerID,
                                 QList<qint16> otherPlayersID,
                                 qint16 attackerID,
                                 qint16 defenderID,
                                 qint16 sizeOfDeck,
                                 QWidget *parent)
    :QWidget{ parent },
     m_playersIDList(otherPlayersID),
     m_thisPlayer{ nullptr },
     m_thisPlayerID{ thisPlayerID },
     m_attackerID{ attackerID },
     m_defenderID{ defenderID },
     m_bufferCard{ nullptr },
     m_instanceChatWindow{ new ChatWindow(ChatWindow::Canal::InGame, this) }
    {
        this->setObjectName("GameTableWidget");
        this->setFixedSize(600, 600);

        m_startDeckWidget = new StartDeckWidget(sizeOfDeck, trumpS, trumpD, this);
        m_startDeckWidget->move(0, this->height() * 2 / 5 - m_startDeckWidget->height() / 2);


        //==============================================================

        for(auto iter :m_playersIDList)
        {
            if(iter == m_thisPlayerID) {
                m_thisPlayer = new ThisPlayerDeckWidget(iter, this);
                m_playersList.push_back(m_thisPlayer);
            } else {
                m_playersList.push_back(new OtherPlayerDeckWidget(iter, this));
            }
        }

        //инициализируем оффера/деффера
        serverSlotSetNewMainPair(m_attackerID, m_defenderID);


        qreal fullAngle = 180.0;
        int countOfAngles = otherPlayersID.size() + 1;
        for(int i = 1; i < countOfAngles; ++i)
        {
            SharedParentForPlayersDeck* deck = m_playersList.at(i - 1);
            if(deck->id() == m_thisPlayerID)
            {
                deck->move(this->width() / 7 - 10, this->height() - (deck->height()));
                continue;
            } else {
                qreal angle = -::qDegreesToRadians(fullAngle * i / (countOfAngles));
                qreal x = this->width() * 0.45 + cos(angle) * this->width() * 0.4;
                qreal y = this->width() * 0.45 + sin(angle) * this->width() * 0.4;
                deck->move(x, y);
            }
        }

        //==============================================================
        m_battleAreaWidget = new BattleAreaWidget({this->width() / 7, this->height() / 4 }, trumpS, this);
        m_battleAreaWidget->resize(this->width() * 5 / 7, this->height() * 2 / 5);
        //==============================================================
        m_handUpWidget = new HandUpWidget(this);
        m_handUpWidget->move(this->width() - m_handUpWidget->width(), this->height() * 2 / 5 - m_handUpWidget->height() / 2);

        //==============================================================

        this->setAutoFillBackground(true);
        QPalette pall(this->palette());
        pall.setColor(QPalette::ColorRole::Background, QColor(0, 100, 0));
        this->setPalette(pall);

        //==============================================================
        //Кнопка конца хода, нажатие приводит к:
        //Отказу от подбрасывания, если ((m_playerQueue == QueueMove::Attacker) || (m_playerQueue == QueueMove::Other))
        //Взятию всех карт из BattleArea, если (m_playerQueue == QueueMove::Defender)
        QPushButton* refusedAction = new QPushButton("RefAct", this);
        refusedAction->setGeometry(5, this->height() - 45, 35, 20);
        QObject::connect(refusedAction, &QPushButton::clicked, this, &GameTableWidget::actionButtonWasClicked);


        m_instanceChatWindow->setGeometry(this->width() * 5 / 7, this->height() * 7 / 10, this->width() * 2 / 7 - 1, this->height() * 3 / 10 - 1);
        QObject::connect(m_instanceChatWindow, &ChatWindow::signalSendMessage, this, &GameTableWidget::messageSignalSendMessage);
        QObject::connect(this, &GameTableWidget::messageSignalReceiveMessage, m_instanceChatWindow, &ChatWindow::slotReceiveMessage);

        this->update();
    }







void GameTableWidget::serverSlotPlayerTakeAllCards(qint16 playerID)
{

    SharedParentForPlayersDeck* player = findDeckForID(playerID);
    foreach(Card* card, m_battleAreaWidget->endOfMove())
    {
        if(playerID == m_thisPlayerID)
        {
            QObject::connect(card, &Card::dragThisElement, this, &GameTableWidget::startCardMove, Qt::ConnectionType::UniqueConnection);
            QObject::connect(card, &Card::movingThisElement, this, &GameTableWidget::playerMoveCard, Qt::ConnectionType::UniqueConnection);
            QObject::connect(card, &Card::dropThisElement, this, &GameTableWidget::playerChangeThisCard, Qt::ConnectionType::UniqueConnection);
        }
        player->putCard(card);
    }
}


void GameTableWidget::serverSlotPlayerTossedCard(qint16 playerID, Card::Suit cardSuit, Card::Dignity cardDignity)
{
    if(playerID == m_thisPlayerID)
    {
        m_battleAreaWidget->tossCard(m_bufferCard);
        m_bufferCard = nullptr;
    }
    else
    {
        m_battleAreaWidget->tossCard(findDeckForID(playerID)->takeCard(cardSuit, cardDignity, this));
    }
}
void GameTableWidget::serverSlotPlayerBeatCard(qint16 playerID, qint16 battlePairID, Card::Suit cardSuit, Card::Dignity cardDignity)
{
    if(playerID == m_thisPlayerID)
    {
        m_battleAreaWidget->beatCard(m_bufferCard, battlePairID);
        m_bufferCard = nullptr;
    }
    else
    {
        m_battleAreaWidget->beatCard(findDeckForID(playerID)->takeCard(cardSuit, cardDignity, this), battlePairID);
    }
}
void GameTableWidget::serverSlotPlayerTransferable(qint16 playerID, Card::Suit cardSuit, Card::Dignity cardDignity)
{
    if(playerID == m_thisPlayerID)
    {
        m_battleAreaWidget->trancferableCard(m_bufferCard);
        m_bufferCard = nullptr;
    }
    else
    {
        m_battleAreaWidget->trancferableCard(this->findDeckForID(playerID)->takeCard(cardSuit, cardDignity, this));
    }
}

void GameTableWidget::serverSlotThisPlayerTakeCardFromDeck(Card::Suit s, Card::Dignity d)
{
    Card* card = m_startDeckWidget->takeCard(s, d, this);
    QObject::connect(card, &Card::dragThisElement, this, &GameTableWidget::startCardMove, Qt::ConnectionType::UniqueConnection);
    QObject::connect(card, &Card::movingThisElement, this, &GameTableWidget::playerMoveCard, Qt::ConnectionType::UniqueConnection);
    QObject::connect(card, &Card::dropThisElement, this, &GameTableWidget::playerChangeThisCard, Qt::ConnectionType::UniqueConnection);
    m_thisPlayer->putCard(card);
}
void GameTableWidget::serverSlotOtherPlayerTakeCardFromDeck(qint16 id)
{
    findDeckForID(id)->putCard(m_startDeckWidget->takeCard(Card::Suit::Club, Card::Dignity::six, this));
}

void GameTableWidget::serverSlotSetNewMainPair(qint16 attacker, qint16 defender)
{
    findDeckForID(m_attackerID)->setQueue(QueueMove::Other);
    findDeckForID(m_defenderID)->setQueue(QueueMove::Other);
    m_attackerID = attacker;
    m_defenderID = defender;
    findDeckForID(m_attackerID)->setQueue(QueueMove::Attacker);
    findDeckForID(m_defenderID)->setQueue(QueueMove::Defender);
}
void GameTableWidget::serverSlotMakeTurn()
{
    foreach(Card* card, m_battleAreaWidget->endOfMove())
    {
        m_handUpWidget->putCard(card);
    }
}

//Неудачные действия.
void GameTableWidget::serverSlotUnsuccesfullyAction(Card::Suit cardSuit, Card::Dignity cardDignity, qint16 pairID)
{
    QObject::connect(m_bufferCard, &Card::dragThisElement, this, &GameTableWidget::startCardMove, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_bufferCard, &Card::movingThisElement, this, &GameTableWidget::playerMoveCard, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_bufferCard, &Card::dropThisElement, this, &GameTableWidget::playerChangeThisCard, Qt::ConnectionType::UniqueConnection);
    m_thisPlayer->putCard(m_bufferCard);
    m_bufferCard = nullptr;
}

void GameTableWidget::playerChangeThisCard(Card* card, QPoint p)
{

    QRect rect(m_battleAreaWidget->pos(), m_battleAreaWidget->size());
    if(rect.contains(p))
    {
        if(m_thisPlayer->queue() == QueueMove::Defender)
        {
            BattlePairWidget* pair = m_battleAreaWidget->checkRightBeatingCard(card, p - m_battleAreaWidget->pos());
            if(pair != nullptr)
            {
                if(pair->state() == BattlePairWidget::PairState::NotBeaten)
                {
                    QObject::disconnect(card, &Card::dragThisElement, this, &GameTableWidget::startCardMove);
                    QObject::disconnect(card, &Card::movingThisElement, this, &GameTableWidget::playerMoveCard);
                    QObject::disconnect(card, &Card::dropThisElement, this, &GameTableWidget::playerChangeThisCard);

                    m_battleAreaWidget->playerLoweredCard(card);
                    emit this->tryBeat(card->suit(), card->dignity(), pair->id());

                    m_bufferCard = card;
                    return;
                }
                else if(pair->state() == BattlePairWidget::PairState::Empty)
                {
                    QObject::disconnect(card, &Card::dragThisElement, this, &GameTableWidget::startCardMove);
                    QObject::disconnect(card, &Card::movingThisElement, this, &GameTableWidget::playerMoveCard);
                    QObject::disconnect(card, &Card::dropThisElement, this, &GameTableWidget::playerChangeThisCard);

                    m_battleAreaWidget->playerLoweredCard(card);
                    emit this->tryTrancferable(card->suit(), card->dignity());

                    m_bufferCard = card;
                    return;
                }
            }
            else
            {
                m_battleAreaWidget->playerLoweredCard(card);
                m_thisPlayer->putCard(card);
                return;
            }
        }
        else
        {
            BattlePairWidget* pair = m_battleAreaWidget->checkRightTossingCard(card);
            if(pair != nullptr)
            {
                QObject::disconnect(card, &Card::dragThisElement, this, &GameTableWidget::startCardMove);
                QObject::disconnect(card, &Card::movingThisElement, this, &GameTableWidget::playerMoveCard);
                QObject::disconnect(card, &Card::dropThisElement, this, &GameTableWidget::playerChangeThisCard);
                m_battleAreaWidget->playerLoweredCard(card);
                emit this->tryToss(card->suit(), card->dignity());

                m_bufferCard = card;
                return;
            }
            else
            {
                m_battleAreaWidget->playerLoweredCard(card);
                m_thisPlayer->putCard(card);
                return;
            }
        }
    }
    else
    {
        m_battleAreaWidget->playerLoweredCard(card);
        m_thisPlayer->putCard(card);
        return;
    }
}
void GameTableWidget::startCardMove(Card* card)
{
    if(m_thisPlayer->queue() == QueueMove::Defender)
        m_battleAreaWidget->playerRaisedCard(card);

    m_thisPlayer->takeCard(card->suit(), card->dignity(), this);
}
void GameTableWidget::playerMoveCard(Card* card, QPoint p)
{
    QRect rect(m_battleAreaWidget->pos(), m_battleAreaWidget->size());
    if(rect.contains(p))
    {
        if(m_thisPlayer->queue() == QueueMove::Defender)
        {
            m_battleAreaWidget->playerMoveCard(card, p - m_battleAreaWidget->pos());
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        m_battleAreaWidget->cardLeaveWidget();
    }
}
SharedParentForPlayersDeck* GameTableWidget::findDeckForID(qint16 playerId)
{
    for(auto it = m_playersList.begin(); it != m_playersList.end(); ++it)
        if((*it)->id() == playerId)
            return (*it);
    return nullptr;
}
