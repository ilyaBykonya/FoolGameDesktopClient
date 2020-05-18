#include "GameTableWidget.h"

GameTableWidget::GameTableWidget(Card::Suit trumpS,
                                 Card::Dignity trumpD,
                                 qint16 thisPlayerID,
                                 QList<qint16> otherPlayersID,
                                 qint16 attackerID,
                                 qint16 defenderID,
                                 QWidget *parent)
    :QWidget{ parent },
     m_playersIDList(otherPlayersID),
     m_thisPlayerID{ thisPlayerID },
     m_attackerID{ attackerID },
     m_defenderID{ defenderID },
     m_thisPlayer{ nullptr }
    {
        qDebug() << "GameTableWidget::ctor";
        this->setObjectName("GameTableWidget");
        this->setFixedSize(400, 600);

        m_startDeckWidget = new StartDeckWidget(36, trumpS, trumpD, this);
        m_startDeckWidget->move(0, this->height() / 2 - m_startDeckWidget->height() / 2);


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
        m_battleAreaWidget = new BattleAreaWidget(trumpS, this);
        m_battleAreaWidget->move(this->width() / 7, this->height() / 3);
        QObject::connect(m_battleAreaWidget, &BattleAreaWidget::tryToss, this, &GameTableWidget::tryToss);
        QObject::connect(m_battleAreaWidget, &BattleAreaWidget::tryBeat, this, &GameTableWidget::tryBeat);
        QObject::connect(m_battleAreaWidget, &BattleAreaWidget::emitText, this, &GameTableWidget::emitText);
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
    }






//Игрок берёт все карты со стола
void GameTableWidget::serverSlotPlayerTakeAllCards(qint16 playerID)
{
    foreach(Card* card, m_battleAreaWidget->endOfMove())
    {
        if(playerID == m_thisPlayerID)
        {
            QObject::connect(card, &Card::dropThisElement, this, &GameTableWidget::playerChangeThisCard, Qt::ConnectionType::UniqueConnection);
            QObject::connect(card, &Card::dragThisElement, this, &GameTableWidget::startCardMove, Qt::ConnectionType::UniqueConnection);
        }
        findDeckForID(playerID)->putCard(card);
    }
}

//какой-то игрок подкинул какую-то крату
void GameTableWidget::serverSlotPlayerTossedCard(qint16 playerID, Card::Suit s, Card::Dignity d)
{
    Card* card = findDeckForID(playerID)->takeCard(s, d, this);
    if(playerID == m_thisPlayerID)
        return;

    m_battleAreaWidget->serverSlotTossCard(card);
}

//какой-то игрок побил какую-то крату какой-то картой
void GameTableWidget::serverSlotPlayerBeatCard(qint16 playerID, qint16 battlePairID, Card::Suit s, Card::Dignity d)
{
    Card* card = findDeckForID(playerID)->takeCard(s, d, this);
    if(playerID == this->m_thisPlayerID)
        return;

    m_battleAreaWidget->serverSlotBeatCard(card, battlePairID);
}


void GameTableWidget::serverSlotThisPlayerTakeCardFromDeck(Card::Suit s, Card::Dignity d)
{
    Card* card = m_startDeckWidget->takeCard(s, d, this);
    QObject::connect(card, &Card::dropThisElement, this, &GameTableWidget::playerChangeThisCard, Qt::ConnectionType::UniqueConnection);
    QObject::connect(card, &Card::dragThisElement, this, &GameTableWidget::startCardMove, Qt::ConnectionType::UniqueConnection);
    m_thisPlayer->putCard(card);
}
void GameTableWidget::serverSlotOtherPlayerTakeCardFromDeck(qint16 id)
{
    findDeckForID(id)->putCard(m_startDeckWidget->takeCard(Card::Suit::Club, Card::Dignity::six, this));
}

void GameTableWidget::serverSlotSetNewMainPair(qint16 attacker, qint16 defender)
{
    emit emitText(QString("GameTableWidget::serverSlotSetNewMainPair[%1:%2]").arg(attacker).arg(defender));
    findDeckForID(m_attackerID)->setQueue(QueueMove::Other);
    findDeckForID(m_defenderID)->setQueue(QueueMove::Other);
    m_attackerID = attacker;
    m_defenderID = defender;
    findDeckForID(m_attackerID)->setQueue(QueueMove::Attacker);
    findDeckForID(m_defenderID)->setQueue(QueueMove::Defender);
}
//Отбой
void GameTableWidget::serverSlotMakeTurn()
{
    foreach(Card* card, m_battleAreaWidget->endOfMove())
    {
        m_handUpWidget->putCard(card);
    }
}

void GameTableWidget::playerChangeThisCard(Card* card, QPoint p)
{
    QRect rect(m_battleAreaWidget->pos(), m_battleAreaWidget->size());
    if(rect.contains(p))
    {
        if(m_thisPlayer->queue() == QueueMove::Defender)
        {
            if(m_battleAreaWidget->beatCard(card, p - m_battleAreaWidget->pos()))
            {
                return;
            }
            else
            {
                m_thisPlayer->putCard(card);
                return;
            }
        }
        else
        {
            if(m_battleAreaWidget->tossCard(card))
            {
                return;
            }
            else
            {
                m_thisPlayer->putCard(card);
                return;
            }
        }
    }
    else
    {
        emit emitText(QString("Card NOT in battle area move {%1:%2:%3:%4}[%5:%6]").arg(m_battleAreaWidget->rect().x()).arg(m_battleAreaWidget->rect().y()).arg(m_battleAreaWidget->rect().width()).arg(m_battleAreaWidget->rect().height()).arg(p.x()).arg(p.y()));
        m_thisPlayer->putCard(card);
        return;
    }
}
void GameTableWidget::startCardMove(Card* card)
{
    m_thisPlayer->takeCard(card->suit(), card->dignity(), this);
}

SharedParentForPlayersDeck* GameTableWidget::findDeckForID(qint16 playerId)
{
    for(auto it = m_playersList.begin(); it != m_playersList.end(); ++it)
        if((*it)->id() == playerId)
            return (*it);
    return nullptr;
}
