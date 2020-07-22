#include "BattleAreaWidget.h"

BattleAreaWidget::BattleAreaWidget(QWidget *parent)
    :QWidget(parent, Qt::WindowType::FramelessWindowHint),
     m_topLine{ new QHBoxLayout },
     m_bottomLine{ new QHBoxLayout },
     m_targetPair{ nullptr },
     m_trancferablePair{ nullptr }
    {
        QVBoxLayout* layout = new QVBoxLayout;
        layout->addLayout(m_topLine);
        layout->addLayout(m_bottomLine);
        this->setLayout(layout);
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

    for(auto it = cardsList.begin(); it != cardsList.end(); ++it)
    {
        (*it)->show();
    }

    this->update();
    return cardsList;
}

BattlePairWidget* BattleAreaWidget::addNewPair()
{
    if(m_pairsList.size() == 6)
        return nullptr;

    BattlePairWidget* newPair = new BattlePairWidget(this->pos(), this);
    m_pairsList.push_back(newPair);
    this->setPairsPosition();
    newPair->show();
    return newPair;
}
void BattleAreaWidget::setPairsPosition()
{
    qint16 index = 0;
    for(auto it = m_pairsList.begin(); it != m_pairsList.end(); ++it, ++index)
    {
        if(index < 3)
            m_topLine->addWidget(*it);
        else
            m_bottomLine->addWidget(*it);
    }
}


bool BattleAreaWidget::checkRightTossingCard()
{
    if(m_pairsList.size() == 6)
        return false;

    return true;
}
bool BattleAreaWidget::checkRightBeatingCard(QPoint p)
{
    BattlePairWidget* pair = findBeatenPairOfCoordinates(p);
    if(pair == nullptr)
    {
        return false;
    }
    if(pair->state() == BattlePairWidget::PairState::Beaten)
    {
        return false;
    }
    //Здесь будут располагаться
    //проверки валидности отбивания

    return true;
}
bool BattleAreaWidget::checkRightTrancferableCard()
{
    if((m_pairsList.size() > 3) || (m_pairsList.isEmpty()))
        return false;

    return true;
}

void BattleAreaWidget::tossCard(Card* card)
{
    cardLeaveWidget();
    BattlePairWidget* newPair = addNewPair();
    if(newPair == nullptr)
        return;

    newPair->tossOnThisPair(card);
}
void BattleAreaWidget::beatCard(Card* card, PairID pairID)
{
    cardLeaveWidget();
    BattlePairWidget* beatenPair = findBeatenPairOfID(pairID);
    if(beatenPair == nullptr)
        return;

    beatenPair->beatThisPair(card);
}
void BattleAreaWidget::trancferableCard(Card* card)
{ 
    cardLeaveWidget();
    BattlePairWidget* newPair = addNewPair();
    if(newPair == nullptr)
        return;

    newPair->tossOnThisPair(card);
}




BattlePairWidget* BattleAreaWidget::findBeatenPairOfCoordinates(QPoint pairPosition)
{
    if(m_pairsList.isEmpty())
        return nullptr;

    for(auto it = m_pairsList.begin(); it != m_pairsList.end(); ++it)
        if(QRect((*it)->pos(), (*it)->size()).contains(pairPosition))
            return (*it);

    return nullptr;
}
BattlePairWidget* BattleAreaWidget::findBeatenPairOfID(PairID pairID)
{
    for(auto it = m_pairsList.begin(); it != m_pairsList.end(); ++it)
        if((*it)->pairID() == pairID)
            return (*it);

    return nullptr;
}




void BattleAreaWidget::playerRaisedCard(bool transferAbility)
{
    if(transferAbility && checkRightTrancferableCard())
        m_trancferablePair = addNewPair();
}
void BattleAreaWidget::playerLoweredCard()
{
    cardLeaveWidget();
    if(m_trancferablePair == nullptr)
        return;

    auto it = m_pairsList.begin();
    for(; it != m_pairsList.end(); ++it)
        if((*it) == m_trancferablePair)
            break;


    if(it != m_pairsList.end())
    {
        if(m_targetPair == m_trancferablePair)
            m_targetPair = nullptr;
        m_pairsList.erase(it);
        m_trancferablePair->deleteLater();
        m_trancferablePair = nullptr;
        setPairsPosition();
    }
}

void BattleAreaWidget::playerMoveCard(Card*, QPoint p)
{
    BattlePairWidget* pair = findBeatenPairOfCoordinates(p);
    if(pair)
    {
        if(m_targetPair == pair)
            return;

        cardLeaveWidget();

        m_targetPair = pair;
        m_targetPair->setTargetState(BattlePairWidget::TargetState::Target);
    }
}
void BattleAreaWidget::cardLeaveWidget()
{
    if(m_targetPair == nullptr)
        return;

    m_targetPair->setTargetState(BattlePairWidget::TargetState::NotTarget);
    m_targetPair = nullptr;
}
