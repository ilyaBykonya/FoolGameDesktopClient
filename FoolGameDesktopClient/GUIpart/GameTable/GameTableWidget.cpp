#include "GameTableWidget.h"

GameTableWidget::GameTableWidget(qint16 thisPlayerID,
                                 QList<qint16> otherPlayersID,
                                 qint16 m_attackerID,
                                 qint16 m_defenderID,
                                 QWidget *parent)
    :QWidget{ parent },
     m_functionalPair{ nullptr, nullptr },
     m_playersIDList(otherPlayersID),
     m_thisPlayerID{ thisPlayerID },
     m_thisPlayer{ nullptr }
    {


        this->setFixedSize(400, 600);

        m_startDeckWidget = new StartDeckWidget(36, Card::Dignity::lady, Card::Suit::Heart, this);
        m_startDeckWidget->move(0, this->height() / 2 - m_startDeckWidget->height() / 2);


        //==============================================================

        for(auto iter :m_playersIDList)
        {
            if(iter == m_thisPlayerID) {
                m_thisPlayer = new ThisPlayerDeckWidget(iter, this);
                m_playersList.push_back(m_thisPlayer);
                QObject::connect(m_thisPlayer, &ThisPlayerDeckWidget::tryBeat, this, &GameTableWidget::slotDefenderChangeThisCard);
                QObject::connect(m_thisPlayer, &ThisPlayerDeckWidget::tryToss, this, &GameTableWidget::slotAttackerChangeThisCard);

                //Тестовые кнопки
                //Потом удалить
                QPushButton* btn = new QPushButton("Do step", this);
                btn->setGeometry(0, this->height() - 20, this->width(), 20);
                QObject::connect(btn, &QPushButton::clicked, [&]()
                {
                    qDebug() << "btn clicked";
                    Card* card = m_startDeckWidget->takeCard(Card::Suit(rand() % 4), Card::Dignity(rand() % 9));
                    if(card != nullptr)
                        m_thisPlayer->putCard(card);
                });
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
                deck->move(this->width() / 7, this->height() - deck->height());
                continue;
            } else {
                qreal angle = -::qDegreesToRadians(fullAngle * i / (countOfAngles));
                qreal x = this->width() * 0.45 + cos(angle) * this->width() * 0.4;
                qreal y = this->width() * 0.45 + sin(angle) * this->width() * 0.4;
                deck->move(x, y);
            }
        }

        //==============================================================

        m_battleAreaWidget = new BattleAreaWidget(this);
        m_battleAreaWidget->move(this->width() / 7, this->height() / 3);

        //==============================================================

        m_handUpWidget = new HandUpWidget(this);
        m_handUpWidget->move(this->width() - m_handUpWidget->width(), this->height() / 2 - m_handUpWidget->height() / 2);

        //==============================================================

        this->setAutoFillBackground(true);
        QPalette pall(this->palette());
        pall.setColor(QPalette::ColorRole::Background, QColor(105, 105, 105));
        this->setPalette(pall);

        //==============================================================
        //Кнопка конца хода, нажатие приводит к:
        //Отказу от подбрасывания, если ((m_playerQueue == QueueMove::Attacker) || (m_playerQueue == QueueMove::Other))
        //Взятию всех карт из BattleArea, если (m_playerQueue == QueueMove::Defender)
        QPushButton* refusedAction = new QPushButton("RefAct", this);
        refusedAction->setGeometry(5, this->height() - 45, 35, 20);
        QObject::connect(refusedAction, &QPushButton::clicked, this, &GameTableWidget::actionButtonWasClicked);

        //==============================================================
        //Тестовая кнопка
        //потом кдалить
        QPushButton* btn2 = new QPushButton("Hand up", this);
        btn2->setGeometry(5, 50, 35, 20);
        QObject::connect(btn2, &QPushButton::clicked, this, &GameTableWidget::serverSlotMakeTurn);
        //==============================================================
    }

//подкидывание
void GameTableWidget::slotAttackerChangeThisCard(Card* card)
{
    //потом соединить сигналы напрямую
    emit tryToss(card);
}

//3 функции для отбивания
void GameTableWidget::slotDefenderChangeThisCard(Card* card)
{
    m_functionalPair.first = card;
    m_functionalPair.second = nullptr;
    slotCheckFunctionlPairForSendToServer();
}
void GameTableWidget::slotPlayerChangeThisBattlePair(BattlePairWidget* pair)
{
    m_functionalPair.second = pair;
    slotCheckFunctionlPairForSendToServer();
}
void GameTableWidget::slotCheckFunctionlPairForSendToServer()
{
    if((m_functionalPair.first == nullptr) || (m_functionalPair.second == nullptr))
        return;

    emit tryBeat(m_functionalPair.first, m_functionalPair.second);
}





//Игрок берёт все карты со стола
void GameTableWidget::serverSlotPlayerTakeAllCards(qint16 playerID)
{
    foreach(Card* card, m_battleAreaWidget->endOfMove())
    {
        findDeckForID(playerID)->putCard(card);
    }
}

//какой-то игрок подкинул какую-то крату
void GameTableWidget::serverSlotPlayerTossedCard(qint16 playerID, Card::Suit s, Card::Dignity d)
{
    m_battleAreaWidget->tossCard(findDeckForID(playerID)->takeCard(s, d));
}

//какой-то игрок побил какую-то крату какой-то картой
void GameTableWidget::serverSlotPlayerBeatCard(qint16 playerID, qint16 battlePairID, Card::Suit s, Card::Dignity d)
{
    m_battleAreaWidget->beatCard(findDeckForID(playerID)->takeCard(s, d), battlePairID);
}

//кто-то берёт карту из колоды
void GameTableWidget::serverSlotPlayerTakeCardFromDeck(qint16 playerID, Card::Suit s, Card::Dignity d)
{
    findDeckForID(playerID)->putCard(m_startDeckWidget->takeCard(s, d));
}

//"сдвиг" оффера деффера
void GameTableWidget::serverSlotSetNewMainPair(qint16 attackerGlobalID, qint16 defenderGlobalID)
{
    for(auto item: m_playersIDList)
    {
        if(item == attackerGlobalID)
            findDeckForID(item)->setQueue(QueueMove::Attacker);
        else if(item == defenderGlobalID)
            findDeckForID(item)->setQueue(QueueMove::Defender);
        else
            findDeckForID(item)->setQueue(QueueMove::Other);
    }
}
//Отбой
void GameTableWidget::serverSlotMakeTurn()
{
    foreach(Card* card, m_battleAreaWidget->endOfMove())
    {
        m_handUpWidget->putCard(card);
    }
}







SharedParentForPlayersDeck* GameTableWidget::findDeckForID(qint16 playerId)
{
    for(auto it = m_playersList.begin(); it != m_playersList.end(); ++it)
        if((*it)->id() == playerId)
            return (*it);
    return nullptr;
}
