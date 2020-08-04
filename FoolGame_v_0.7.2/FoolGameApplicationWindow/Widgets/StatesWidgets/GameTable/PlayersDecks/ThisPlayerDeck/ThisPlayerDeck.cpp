#include "ThisPlayerDeck.h"


ThisPlayerDeck::ThisPlayerDeck(GameUserInformation* userInfo, QWidget *parent)
    :SharedPlayersDeckParent{ userInfo, parent }
    {
        this->setObjectName("ThisUserDeck");
        this->setFixedHeight(110);
    }

quint8 ThisPlayerDeck::amountOfCards() const
{
    return m_playerCardsList.size();
}


void ThisPlayerDeck::putCard(Card* card)
{
    if(card == nullptr)
        return;

    if(std::find(m_playerCardsList.begin(), m_playerCardsList.end(), card) != m_playerCardsList.end())
        return;


    m_playerCardsList.push_back(card);
    card->setNewLocation(Card::LocationState::InPlayerDeck);
    QObject::connect(card, &Card::endOfAnimation, this, &ThisPlayerDeck::setNormalSize, Qt::ConnectionType::UniqueConnection);
    std::sort(m_playerCardsList.begin(), m_playerCardsList.end(), &Card::less);
    card->doAnimationOnPoint(QPoint(this->x() + this->width() / 2, this->y()));
}
Card* ThisPlayerDeck::takeCard(Card::Suit cardSuit, Card::Dignity cardDignity, QWidget*)
{
    for(auto card = m_playerCardsList.begin(); card != m_playerCardsList.end(); ++card)
    {
        if(((*card)->suit() == cardSuit) && ((*card)->dignity() == cardDignity))
        {
            Card* buf = (*card);
            QObject::disconnect(buf, &Card::endOfAnimation, this, &ThisPlayerDeck::setNormalSize);
            m_playerCardsList.erase(card);
            this->setNormalSize();
            return buf;
        }
    }
    return nullptr;
}

void ThisPlayerDeck::setNormalSize()
{
    quint16 startPos = this->width() / 2 - (m_playerCardsList.size() * 20 / 2) + 5;
    quint8 cardIndex = 0;
    for(auto it = m_playerCardsList.begin(); it != m_playerCardsList.end(); ++cardIndex, ++it)
    {
        (*it)->move(this->pos() + QPoint(cardIndex * 20 + startPos, 5));
        (*it)->raise();
        (*it)->repaint();
    }
    this->repaint();
}
void ThisPlayerDeck::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::PenStyle::NoPen));
    switch (m_playerQueue)
    {
        case QueueMove::Attacker: painter.setBrush(QBrush(Qt::GlobalColor::red)); break;
        case QueueMove::Other:    painter.setBrush(QBrush(Qt::GlobalColor::yellow)); break;
        case QueueMove::Defender: painter.setBrush(QBrush(Qt::GlobalColor::green)); break;
    }
    painter.drawEllipse(QRect(5, this->height() / 2 - 8, 16, 16));
}
