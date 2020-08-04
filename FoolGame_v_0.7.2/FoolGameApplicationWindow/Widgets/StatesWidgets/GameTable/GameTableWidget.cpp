#include "GameTableWidget.h"

GameTableWidget::GameTableWidget(Card::Suit trumpS,
                                 Card::Dignity trumpD,
                                 UserID thisPlayerID,
                                 QList<GameUserInformation*> allPlayers,
                                 UserID attackerID,
                                 UserID defenderID,
                                 DeckSize sizeOfDeck,
                                 QWidget *parent)
    :QWidget{ parent },
     m_thisPlayer{ nullptr },
     m_thisPlayerID{ thisPlayerID },
     m_attackerID{ attackerID },
     m_defenderID{ defenderID },
     m_bufferCard{ nullptr },
     m_tableLayout{ new QGridLayout }
    {
        this->setObjectName("GameTable");
        this->resize(500, 470);
        //==============================================================

        //==============================================================

        m_startDeckWidget = new StartDeckWidget(sizeOfDeck, trumpS, trumpD, this);
        m_tableLayout->addWidget(m_startDeckWidget, 15, 0, 10, 2);

        //==============================================================

        for(auto it = allPlayers.begin(); it != allPlayers.end(); ++it)
        {
            m_playersIDList.push_back((*it)->userID());
            if((*it)->userID() == thisPlayerID)
            {
                m_thisPlayer = new ThisPlayerDeck((*it), this);
                m_playersList.push_back(m_thisPlayer);
            }
            else
            {
                m_playersList.push_back(new OtherPlayerDeck((*it), this));
            }
        }

        //==============================================================
        //инициализируем оффера/деффера
        serverSlotSetNewMainPair(m_attackerID, m_defenderID);

        //==============================================================

        quint8 otherIndex = 0;
        for(auto deck = m_playersList.begin(); deck < m_playersList.end(); ++deck)
        {
            if((*deck)->user()->userID() == m_thisPlayerID)
            {
                m_tableLayout->addWidget((*deck), 32, 0, 8, countOfColumns);
                continue;
            } else {
                int xPos = qFloor((qreal(countOfColumns) * (otherIndex + 1) / allPlayers.size()));
                int yPos = 1 + round(pow(abs(8 - xPos) / 3, 1.2));
                m_tableLayout->addWidget((*deck), yPos, xPos, 3, 2);
                ++otherIndex;
            }
        }
        //==============================================================

        m_battleAreaWidget = new BattleAreaWidget(this);
        m_tableLayout->addWidget(m_battleAreaWidget, 6, 3, 24, 11);

        //==============================================================

        m_handUpWidget = new HandUpWidget(this);
        m_tableLayout->addWidget(m_handUpWidget, 15, 16, 10, 2);

        //==============================================================



        //=============================================================
        //На этом виджете бдует лежать арена
        QWidget* allArenaElementsWindow = new QWidget;
        allArenaElementsWindow->setLayout(m_tableLayout);

        //==============================================================













        QFrame* footerElementsWindow = new QFrame;
        footerElementsWindow->setFrameStyle(QFrame::Shape::Panel | QFrame::Shadow::Raised);
        QHBoxLayout* footerLayout = new QHBoxLayout;
        footerElementsWindow->setLayout(footerLayout);

        //==============================================================
        //Кнопка конца хода, нажатие приводит к:
        //Отказу от подбрасывания, если ((m_playerQueue == QueueMove::Attacker) || (m_playerQueue == QueueMove::Other))
        //Взятию всех карт из BattleArea, если (m_playerQueue == QueueMove::Defender)
        QPushButton* refusedAction = new QPushButton("Refused\n"
                                                     "Action");
        QObject::connect(refusedAction, &QPushButton::clicked, this, &GameTableWidget::actionButtonWasClicked);

        footerLayout->addWidget(refusedAction);







        for(quint8 i = 0; i < countOfRows; ++i)
            m_tableLayout->setRowStretch(i, 1);
        for(quint8 i = 0; i < countOfColumns; ++i)
            m_tableLayout->setColumnStretch(i, 1);

        m_tableLayout->setSpacing(0);
        m_tableLayout->setMargin(0);
        m_tableLayout->setSizeConstraint(QGridLayout::SizeConstraint::SetMinAndMaxSize);

        //==============================================================




        QVBoxLayout* allElementsLayout = new QVBoxLayout;
            allElementsLayout->addWidget(allArenaElementsWindow, 18);
            allElementsLayout->addWidget(footerElementsWindow, 1);
            allElementsLayout->setSpacing(0);
            allElementsLayout->setMargin(0);
        this->setLayout(allElementsLayout);
    }










void GameTableWidget::serverSlotPlayerTossedCard(UserID playerID, Card::Suit cardSuit, Card::Dignity cardDignity)
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
void GameTableWidget::serverSlotPlayerBeatCard(UserID playerID, PairID battlePairID, Card::Suit cardSuit, Card::Dignity cardDignity)
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
void GameTableWidget::serverSlotPlayerTransferable(UserID playerID, Card::Suit cardSuit, Card::Dignity cardDignity)
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

void GameTableWidget::serverSlotUnsuccesfullyAction()
{
    QObject::connect(m_bufferCard, &Card::dragThisElement, this, &GameTableWidget::slotStartCardMove, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_bufferCard, &Card::movingThisElement, this, &GameTableWidget::slotPlayerMoveCard, Qt::ConnectionType::UniqueConnection);
    QObject::connect(m_bufferCard, &Card::dropThisElement, this, &GameTableWidget::slotPlayerChangeThisCard, Qt::ConnectionType::UniqueConnection);
    m_thisPlayer->putCard(m_bufferCard);
    m_bufferCard = nullptr;
}





void GameTableWidget::serverSlotThisPlayerTakeCardFromDeck(Card::Suit cardSuit, Card::Dignity cardDignity)
{
    Card* card = m_startDeckWidget->takeCard(cardSuit, cardDignity, this);
    QObject::connect(card, &Card::dragThisElement, this, &GameTableWidget::slotStartCardMove, Qt::ConnectionType::UniqueConnection);
    QObject::connect(card, &Card::movingThisElement, this, &GameTableWidget::slotPlayerMoveCard, Qt::ConnectionType::UniqueConnection);
    QObject::connect(card, &Card::dropThisElement, this, &GameTableWidget::slotPlayerChangeThisCard, Qt::ConnectionType::UniqueConnection);
    m_thisPlayer->putCard(card);
}
void GameTableWidget::serverSlotOtherPlayerTakeCardFromDeck(UserID playerID)
{
    findDeckForID(playerID)->putCard(m_startDeckWidget->takeCard(Card::Suit::Club, Card::Dignity::six, this));
}




void GameTableWidget::serverSlotSetNewMainPair(UserID attacker, UserID defender)
{
    findDeckForID(m_attackerID)->setQueue(SharedPlayersDeckParent::QueueMove::Other);
    findDeckForID(m_defenderID)->setQueue(SharedPlayersDeckParent::QueueMove::Other);
    m_attackerID = attacker;
    m_defenderID = defender;
    findDeckForID(m_attackerID)->setQueue(SharedPlayersDeckParent::QueueMove::Attacker);
    findDeckForID(m_defenderID)->setQueue(SharedPlayersDeckParent::QueueMove::Defender);
}
void GameTableWidget::serverSlotPlayerTakeAllCards(UserID playerID)
{

    SharedPlayersDeckParent* player = findDeckForID(playerID);
    foreach(Card* card, m_battleAreaWidget->endOfMove())
    {
        if(playerID == m_thisPlayerID)
        {
            QObject::connect(card, &Card::dragThisElement, this, &GameTableWidget::slotStartCardMove, Qt::ConnectionType::UniqueConnection);
            QObject::connect(card, &Card::movingThisElement, this, &GameTableWidget::slotPlayerMoveCard, Qt::ConnectionType::UniqueConnection);
            QObject::connect(card, &Card::dropThisElement, this, &GameTableWidget::slotPlayerChangeThisCard, Qt::ConnectionType::UniqueConnection);
        }
        player->putCard(card);
    }

}
void GameTableWidget::serverSlotMakeTurn()
{
    foreach(Card* card, m_battleAreaWidget->endOfMove())
    {
        m_handUpWidget->putCard(card);
    }
}





void GameTableWidget::slotStartCardMove(Card* card)
{
    if(m_thisPlayer->queue() == SharedPlayersDeckParent::QueueMove::Defender)
        m_battleAreaWidget->playerRaisedCard(true);

    m_thisPlayer->takeCard(card->suit(), card->dignity(), this);
    card->raise();
}
void GameTableWidget::slotPlayerMoveCard(Card* card, QPoint p)
{
    QRect rect(m_battleAreaWidget->pos(), m_battleAreaWidget->size());
    if(rect.contains(p))
    {
        m_battleAreaWidget->playerMoveCard(card, p - m_battleAreaWidget->pos());
    }
    else
    {
        m_battleAreaWidget->cardLeaveWidget();
    }
}
void GameTableWidget::slotPlayerChangeThisCard(Card* card, QPoint p)
{

    QRect rect(m_battleAreaWidget->pos(), m_battleAreaWidget->size());
    if(rect.contains(p))
    {
        if(m_thisPlayer->queue() == SharedPlayersDeckParent::QueueMove::Defender)
        {
            BattlePairWidget* pair = m_battleAreaWidget->findBeatenPairOfCoordinates(p - m_battleAreaWidget->pos());
            if(pair != nullptr)
            {
                if(pair->state() == BattlePairWidget::PairState::NotBeaten)
                {
                    m_battleAreaWidget->playerLoweredCard();
                    QObject::disconnect(card, &Card::dragThisElement, this, &GameTableWidget::slotStartCardMove);
                    QObject::disconnect(card, &Card::movingThisElement, this, &GameTableWidget::slotPlayerMoveCard);
                    QObject::disconnect(card, &Card::dropThisElement, this, &GameTableWidget::slotPlayerChangeThisCard);

                    m_bufferCard = card;
                    emit this->tryBeat(pair->pairID(), card->suit(), card->dignity());
                }
                else if(pair->state() == BattlePairWidget::PairState::Empty)
                {
                    m_battleAreaWidget->playerLoweredCard();
                    QObject::disconnect(card, &Card::dragThisElement, this, &GameTableWidget::slotStartCardMove);
                    QObject::disconnect(card, &Card::movingThisElement, this, &GameTableWidget::slotPlayerMoveCard);
                    QObject::disconnect(card, &Card::dropThisElement, this, &GameTableWidget::slotPlayerChangeThisCard);

                    m_bufferCard = card;
                    emit this->tryTrancferable(card->suit(), card->dignity());
                }
                else
                {
                    m_battleAreaWidget->playerLoweredCard();
                    m_thisPlayer->putCard(card);
                }
            }
            else
            {
                m_battleAreaWidget->playerLoweredCard();
                m_thisPlayer->putCard(card);
            }
        }
        else
        {
            m_battleAreaWidget->playerLoweredCard();
            QObject::disconnect(card, &Card::dragThisElement, this, &GameTableWidget::slotStartCardMove);
            QObject::disconnect(card, &Card::movingThisElement, this, &GameTableWidget::slotPlayerMoveCard);
            QObject::disconnect(card, &Card::dropThisElement, this, &GameTableWidget::slotPlayerChangeThisCard);

            m_bufferCard = card;
            emit this->tryToss(card->suit(), card->dignity());
        }
    }
    else
    {
        m_battleAreaWidget->playerLoweredCard();
        m_thisPlayer->putCard(card);
    }
}




SharedPlayersDeckParent* GameTableWidget::findDeckForID(UserID playerId)
{
    for(auto it = m_playersList.begin(); it != m_playersList.end(); ++it)
        if((*it)->user()->userID() == playerId)
            return (*it);

    return nullptr;
}
