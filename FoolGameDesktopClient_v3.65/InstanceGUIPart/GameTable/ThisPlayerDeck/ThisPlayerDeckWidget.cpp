#include "ThisPlayerDeckWidget.h"

ThisPlayerDeckWidget::ThisPlayerDeckWidget(UserID id, QWidget *parent)
    :SharedParentForPlayersDeck{ id, parent }
    {
        this->setMouseTracking(true);
        this->setFixedHeight(110);
    }

quint8 ThisPlayerDeckWidget::amountOfCards() const
{
    return m_playerCardsList.size();
}


void ThisPlayerDeckWidget::putCard(Card* card)
{
    if(card == nullptr)
        return;

    if(std::find(m_playerCardsList.begin(), m_playerCardsList.end(), card) != m_playerCardsList.end())
        return;


    m_playerCardsList.push_back(card);
    card->setNewLocation(Card::LocationState::InPlayerDeck);
    QObject::connect(card, &Card::endOfAnimation, this, &ThisPlayerDeckWidget::setNormalSize, Qt::ConnectionType::UniqueConnection);
    std::sort(m_playerCardsList.begin(), m_playerCardsList.end(), &Card::less);
    card->doAnimationOnPoint(this->pos());
}
Card* ThisPlayerDeckWidget::takeCard(Card::Suit cardSuit, Card::Dignity cardDignity, QWidget*)
{
    for(auto card = m_playerCardsList.begin(); card != m_playerCardsList.end(); ++card)
    {
        if(((*card)->suit() == cardSuit) && ((*card)->dignity() == cardDignity))
        {
            Card* buf = (*card);
            QObject::disconnect(buf, &Card::endOfAnimation, this, &ThisPlayerDeckWidget::setNormalSize);
            m_playerCardsList.erase(card);
            this->setNormalSize();
            return buf;
        }
    }
    return nullptr;
}

void ThisPlayerDeckWidget::setNormalSize()
{
    qint16 weight = 20 * m_playerCardsList.size() + 40;
    this->resize(weight, this->height());
    qint16 i = 0;

    for(auto it = m_playerCardsList.begin(); it != m_playerCardsList.end(); ++i, ++it)
    {
        (*it)->move(this->pos() + QPoint(i * 20 + 5, 30));
        (*it)->raise();
        (*it)->repaint();
    }
    this->repaint();
}


void ThisPlayerDeckWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(Qt::GlobalColor::black));
        switch (m_playerQueue)
        {
            case QueueMove::Attacker: painter.setPen(QPen(Qt::GlobalColor::red,    4)); break;
            case QueueMove::Other:    painter.setPen(QPen(Qt::GlobalColor::yellow, 4)); break;
            case QueueMove::Defender: painter.setPen(QPen(Qt::GlobalColor::green,  4)); break;
        }
        painter.drawRect(rect());
}