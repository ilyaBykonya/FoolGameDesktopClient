#include "BattleAreaWidget.h"

BattleAreaWidget::BattleAreaWidget(Card::Suit t, QWidget *parent)
    :QWidget{ parent },
     m_topLine{ new QHBoxLayout },
     m_bottomLine{ new QHBoxLayout },
     m_trump{ t }
    {
        this->setObjectName("BattleAreaWidget");
        this->setFixedSize(280, 250);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addLayout(m_topLine);
        layout->addLayout(m_bottomLine);
        this->setLayout(layout);
    }


void BattleAreaWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(75, 0, 130), Qt::BrushStyle::Dense3Pattern));
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
        (*it)->reset();
        (*it)->show();
    }

    return cardsList;
}


void BattleAreaWidget::setPairsPosition(BattlePairWidget* pair)
{
    if(m_pairsList.size() > 3)
    {
        m_bottomLine->addWidget(pair);
    }
    else
    {
        m_topLine->addWidget(pair);
    }
}
bool BattleAreaWidget::tossCard(Card* card)
{
    BattlePairWidget* newPair = new BattlePairWidget(card, this);
    m_pairsList.push_back(newPair);
    setPairsPosition(newPair);
    newPair->show();
    emit tryToss(card);

    QPoint p(((m_pairsList.size() % 3) - 1) * 70 + 30, (m_pairsList.size() / 4) * this->height() / 2);
    card->doAnimationOnPoint(this->pos() + p);
    return true;
}
void BattleAreaWidget::serverSlotTossCard(Card* card)
{
    BattlePairWidget* newPair = new BattlePairWidget(card, this);
    m_pairsList.push_back(newPair);
    setPairsPosition(newPair);
    newPair->show();

    QPoint p(((m_pairsList.size() % 3) - 1) * 70 + 30, (m_pairsList.size() / 4) * this->height() / 2);
    card->doAnimationOnPoint(this->pos() + p);
}


BattlePairWidget* BattleAreaWidget::findBeatenPair(QPoint p)
{
    if(m_pairsList.isEmpty())
        return nullptr;
    qDebug() << (QString("BattleAreaWidget::findBeatenPair::rect[%1:%2:%3:%4]").arg(rect().x()).arg(rect().y()).arg(rect().width()).arg(rect().height()));
    qDebug() << (QString("BattleAreaWidget::findBeatenPair::point[%1:%2]").arg(p.x()).arg(p.y()));
    qint16 index = 0;
    if(m_pairsList.size() < 4)
    {
        qDebug() << (QString("BattleAreaWidget::beatenPairID::step_0"));
        index = p.x() / (this->width() / m_pairsList.size());
    }
    else
    {
        if(p.y() < this->height() / 2)
        {
            qDebug() << (QString("BattleAreaWidget::beatenPairID::step_1"));
            index = p.x() / (this->width() / 3);
        }
        else
        {
            qDebug() << (QString("BattleAreaWidget::beatenPairID::step_2"));
            index = p.x() / (this->width() / (m_pairsList.size() - 3)) + 3;
        }
    }
    if((index >= m_pairsList.size()) || (index < 0))
        return nullptr;
    BattlePairWidget* wid = m_pairsList.at(index);
    if(wid->state() == BattlePairWidget::PairState::Beaten)
        return nullptr;
    qDebug() << (QString("BattleAreaWidget::findBeatenPair::index[%1]").arg(index));
    return wid;
}
bool BattleAreaWidget::beatCard(Card* card, QPoint p)
{
    qDebug() << QString("BattleAreaWidget::beatCard[%1:%2][%3:4]").arg(card->suit()).arg(card->dignity()).arg(p.x()).arg(p.y());
    BattlePairWidget* pair = findBeatenPair(p);
    if(pair == nullptr)
    {
        qDebug() << "BattleAreaWidget::beatCard::ERROR(Pair is nullptr)";
        return false;
    }
    if(card == nullptr)
    {
        qDebug() << "BattleAreaWidget::beatCard::ERROR(Card is nullptr)";
        return false;
    }
    //Здесь будут располагаться
    //проверки валидности отбивания

    pair->beatThisPair(card);
    emit tryBeat(card, pair->id());
    card->doAnimationOnPoint(this->pos() + pair->pos());
    return true;
}
void BattleAreaWidget::serverSlotBeatCard(Card* card, qint16 pairID)
{
    foreach(BattlePairWidget* pair, m_pairsList)
    {
        if(pair->id() == pairID)
        {
            pair->beatThisPair(card);
            qint16 index = m_pairsList.indexOf(pair);
            QPoint p((index % 3) * 70 + 30, (index / 3) * this->height() / 2);
            card->doAnimationOnPoint(this->pos() + p);
        }
    }
}
