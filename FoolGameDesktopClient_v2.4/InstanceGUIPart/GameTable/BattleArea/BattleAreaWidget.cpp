#include "BattleAreaWidget.h"

BattleAreaWidget::BattleAreaWidget(QPoint thisPosition, Card::Suit t, QWidget *parent)
    :QWidget(parent, Qt::WindowType::FramelessWindowHint),
     m_topLine{ new QHBoxLayout },
     m_bottomLine{ new QHBoxLayout },
     m_trump{ t },
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

    return this->setPairsPosition(new BattlePairWidget(m_thisRealPos, this));
}
BattlePairWidget* BattleAreaWidget::setPairsPosition(BattlePairWidget* pair)
{
    m_pairsList.push_back(pair);
    if(m_pairsList.size() > 3)
        m_bottomLine->addWidget(pair);
    else
        m_topLine->addWidget(pair);

    pair->hide();
    return pair;
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
    if(pair->state() != BattlePairWidget::PairState::NotBeaten)
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

    if(m_pairsList.last()->state() != BattlePairWidget::PairState::Empty)
        return false;

    m_pairsList.last()->show();
    m_pairsList.last()->tossOnThisPair(card);

    addNewPair();

    return true;
}
bool BattleAreaWidget::beatCard(Card* card, qint16 pairID)
{

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

BattlePairWidget* BattleAreaWidget::findBeatenPair(QPoint p)
{
    if(m_pairsList.isEmpty())
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


