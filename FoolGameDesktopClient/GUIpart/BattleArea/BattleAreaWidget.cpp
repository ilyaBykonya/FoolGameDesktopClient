#include "BattleAreaWidget.h"

BattleAreaWidget::BattleAreaWidget(QWidget *parent)
    :QWidget{ parent },
     m_topLine{ new QHBoxLayout() },
     m_bottomLine{ new QHBoxLayout() }

    {
        this->setFixedSize(280, 250);

        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->addLayout(m_topLine);
        mainLayout->addLayout(m_bottomLine);
        this->setLayout(mainLayout);
    }


void BattleAreaWidget::setPairsPosition(BattlePairWidget* pair)
{
    if(m_pairsList.size() < 4)
        m_topLine->addWidget(pair);
    else
        m_bottomLine->addWidget(pair);
}




void BattleAreaWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(75, 0, 130), Qt::BrushStyle::Dense3Pattern));
    painter.drawRect(this->rect());
}

QList<Card*>&& BattleAreaWidget::endOfMove()
{
    QList<Card*> m_cards;
    while(m_pairsList.begin() != m_pairsList.end())
    {
        BattlePairWidget* pair = m_pairsList.first();
        if(pair->firstCard() != nullptr)
            m_cards.push_back(pair->firstCard());
        if(pair->secondCard() != nullptr)
            m_cards.push_back(pair->secondCard());

        delete pair;
        m_pairsList.pop_front();
    }
    this->repaint();

    return std::move(m_cards);
}



void BattleAreaWidget::tossCard(Card* card)
{
    BattlePairWidget* newPair = new BattlePairWidget(card, this);
    QObject::connect(newPair, &BattlePairWidget::clickToThisPair, this, &BattleAreaWidget::playerWantBeatThisCard);
    newPair->show();
}
void BattleAreaWidget::beatCard(Card* card, qint16 pairID)
{
    foreach(BattlePairWidget* pair, m_pairsList)
    {
        if(pair->id() == pairID)
        {
            pair->beatThisPair(card);
            return;
        }
    }
}
