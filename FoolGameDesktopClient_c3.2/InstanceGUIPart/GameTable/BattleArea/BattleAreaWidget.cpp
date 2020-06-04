#include "BattleAreaWidget.h"

BattleAreaWidget::BattleAreaWidget(QPoint thisPosition, Card::Suit t, QWidget *parent)
    :QWidget(parent, Qt::WindowType::FramelessWindowHint),
     m_topLine{ new QHBoxLayout },
     m_bottomLine{ new QHBoxLayout },
     m_trump{ t },
     m_targetPair{ nullptr },
     m_thisRealPos{ thisPosition }
    {
        QVBoxLayout* layout = new QVBoxLayout;
        layout->addLayout(m_topLine);
        layout->addLayout(m_bottomLine);
        this->setLayout(layout);
        this->move(m_thisRealPos);
        this->setFixedSize(280, 250);
        addNewPair();
    }


void BattleAreaWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(0, 100, 0), Qt::BrushStyle::Dense3Pattern));
    painter.drawRect(this->rect());
}

QList<Card*> BattleAreaWidget::endOfMove()
{
    cardLeaveWidget();
    QList<Card*> cardsList;
    while(m_pairsList.begin() != m_pairsList.end())
    {
        BattlePairWidget* pair = m_pairsList.first();
        if(pair->firstCard() != nullptr)
            cardsList.push_back(pair->firstCard());
        if(pair->secondCard() != nullptr)
            cardsList.push_back(pair->secondCard());

        delete pair;
        m_pairsList.pop_front();
    }
    this->repaint();

    for(auto it = cardsList.begin(); it != cardsList.end(); ++it)
    {
        (*it)->show();
    }
    addNewPair();
    return cardsList;
}

BattlePairWidget* BattleAreaWidget::addNewPair()
{
    if(m_pairsList.size() == 6)
        return nullptr;

    m_pairsList.push_back(new BattlePairWidget(m_thisRealPos, this));
    return this->setPairsPosition();
}
BattlePairWidget* BattleAreaWidget::setPairsPosition()
{
    qint16 index = 0;
    for(auto it = m_pairsList.begin(); it != m_pairsList.end(); ++it, ++index)
    {
        if(index < 3)
            m_topLine->addWidget(*it);
        else
            m_bottomLine->addWidget(*it);

        if((*it)->state() == BattlePairWidget::PairState::Empty)
            (*it)->hide();
        else
            (*it)->show();
    }
}


BattlePairWidget* BattleAreaWidget::checkRightTossingCard(Card* cardTossingCard)
{
    if(m_pairsList.size() == 1)
        return m_pairsList.first();
    if(m_pairsList.last()->state() != BattlePairWidget::PairState::Empty)
        return nullptr;

    //TEST
    return m_pairsList.last();

    for(auto it = m_pairsList.begin(); it != m_pairsList.end(); ++it)
    {
        Card* card = (*it)->firstCard();
        if(card != nullptr)
            if(card->dignity() == cardTossingCard->dignity())
                return m_pairsList.last();

        card = (*it)->secondCard();
        if(card != nullptr)
            if(card->dignity() == cardTossingCard->dignity())
                return m_pairsList.last();
    }

    return nullptr;
}
BattlePairWidget* BattleAreaWidget::checkRightBeatingCard(Card* card, QPoint p)
{
    BattlePairWidget* pair = findBeatenPair(p);
    if(pair == nullptr)
    {
        return nullptr;
    }
    if(pair->state() == BattlePairWidget::PairState::Beaten)
    {
        return nullptr;
    }
    if(card == nullptr)
    {
        return nullptr;
    }
    //Здесь будут располагаться
    //проверки валидности отбивания

    return pair;
}

bool BattleAreaWidget::tossCard(Card* card)
{
    cardLeaveWidget();
    if(m_pairsList.last()->state() != BattlePairWidget::PairState::Empty)
        return false;

    m_pairsList.last()->show();
    m_pairsList.last()->tossOnThisPair(card);

    addNewPair();

    return true;
}
bool BattleAreaWidget::beatCard(Card* card, qint16 pairID)
{
    cardLeaveWidget();
    for(auto it = m_pairsList.begin(); it != m_pairsList.end(); ++it)
    {
        if((*it)->id() == pairID)
        {
            if((*it)->state() != BattlePairWidget::PairState::NotBeaten)
                continue;

            (*it)->beatThisPair(card);
            return true;
        }
    }

    return false;
}
bool BattleAreaWidget::trancferableCard(Card* card)
{
    cardLeaveWidget();
    if(m_pairsList.size() > 4)
        return false;

    m_pairsList.last()->show();
    m_pairsList.last()->tossOnThisPair(card);

    addNewPair();

    return true;
}

Card* BattleAreaWidget::cancelToss(Card::Suit cardSuit, Card::Dignity cardDignity, qint16 pairID)
{
    for(auto it = m_pairsList.begin(); it != m_pairsList.end(); ++it)
    {
        if((*it)->id() == pairID)
        {
            if((*it)->state() == BattlePairWidget::PairState::Beaten)
                return nullptr;


                Card* buf = (*it)->cancelToss();
                delete (*it);
                m_pairsList.erase(it);
                setPairsPosition();

                if((m_pairsList.size() == 5)  && (m_pairsList.last()->state() != BattlePairWidget::PairState::Empty))
                    addNewPair();

                return buf;
        }
    }
    return nullptr;
}
Card* BattleAreaWidget::cancelBeat(Card::Suit cardSuit, Card::Dignity cardDignity, qint16 pairID)
{
    BattlePairWidget* pair = findPairOfID(pairID);
    if(pair == nullptr)
        return nullptr;

    if(pair->state() != BattlePairWidget::PairState::Beaten)
        return nullptr;

    return pair->cancelBeat();

}


BattlePairWidget* BattleAreaWidget::findBeatenPair(QPoint p)
{
    if(m_pairsList.isEmpty() || m_pairsList.size() == 1)
        return nullptr;

    qint16 index = 0;
    if(m_pairsList.size() < 4)
    {
        index = p.x() / (this->width() / m_pairsList.size());
    }
    else
    {
        if(p.y() < this->height() / 2)
        {
            index = p.x() / (this->width() / 3);
        }
        else
        {
            index = p.x() / (this->width() / (m_pairsList.size() - 3)) + 3;
        }
    }

    if((index >= m_pairsList.size()) || (index < 0))
        return nullptr;

    return m_pairsList.at(index);
}
BattlePairWidget* BattleAreaWidget::findPairOfID(qint16 pairID)
{
    for(auto it = m_pairsList.begin(); it != m_pairsList.end(); ++it)
        if((*it)->id() == pairID)
            return (*it);

    return nullptr;
}


void BattleAreaWidget::playerRaisedCard(Card*)
{
    if((m_pairsList.size() < 5) && (m_pairsList.size() > 1))
        m_pairsList.last()->show();
}
void BattleAreaWidget::playerMoveCard(Card*, QPoint p)
{
    qDebug() << "   AREA: playerMoveCard ";
    BattlePairWidget* pair = findBeatenPair(p);
    if(pair)
    {
        if(m_targetPair == pair)
            return;

        cardLeaveWidget();

        m_targetPair = pair;
        m_targetPair->setTargetState(BattlePairWidget::TargetState::Target);
    }
    else
    {
        return;
    }
}
void BattleAreaWidget::cardLeaveWidget()
{
    if(m_targetPair == nullptr)
        return;

    m_targetPair->setTargetState(BattlePairWidget::TargetState::NotTarget);
    m_targetPair = nullptr;
}
void BattleAreaWidget::playerLoweredCard(Card*)
{
    if((m_pairsList.last()->state() == BattlePairWidget::PairState::Empty) && (m_pairsList.last()->firstCard() == nullptr))
        m_pairsList.last()->hide();
}
