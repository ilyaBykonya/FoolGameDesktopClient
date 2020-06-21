#include "OtherPlayerDeckWidget.h"

OtherPlayerDeckWidget::OtherPlayerDeckWidget(UserID id, QWidget *parent)
    :SharedParentForPlayersDeck{ id, parent },
     m_countOfCards{ 0 },
     m_cardShirtPixmap{ "D:/FoolGame/FoolGameDesktopClient/pictures/Cards/cardShirt.jpg" }
    {
        this->setObjectName("OtherPlayerDeckWidget");
        this->setNormalSize();
    }

void OtherPlayerDeckWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(255, 0, 0), Qt::BrushStyle::Dense3Pattern));
    switch (m_playerQueue)
    {
        case QueueMove::Attacker: painter.setPen(QPen(Qt::GlobalColor::red, 4));    break;
        case QueueMove::Other:    painter.setPen(QPen(Qt::GlobalColor::yellow, 4)); break;
        case QueueMove::Defender: painter.setPen(QPen(Qt::GlobalColor::green, 4));  break;
    }
    painter.drawRect(this->rect());

    for(quint8 i = 0; i < m_countOfCards; ++i)
        painter.drawPixmap(QRect({2 + i * 7, 2}, {m_cardShirtPixmap.size() / 3}), m_cardShirtPixmap);
}

quint8 OtherPlayerDeckWidget::amountOfCards() const
{
    return m_countOfCards;
}
void OtherPlayerDeckWidget::putCard(Card* card)
{
    ++m_countOfCards;
    card->setNewLocation(Card::LocationState::InOtherPlayerDeck);
    QObject::connect(card, &Card::endOfAnimation, this, &OtherPlayerDeckWidget::setNormalSize);
    QObject::connect(card, &Card::endOfAnimation, card, &QObject::deleteLater);
    card->doAnimationOnPoint(this->pos());
}
Card* OtherPlayerDeckWidget::takeCard(Card::Suit cardSuit, Card::Dignity cardDignity, QWidget* cardParent)
{
    if(m_countOfCards > 0)
        --m_countOfCards;

    this->setNormalSize();
    Card* card = new Card(cardSuit, cardDignity, cardParent);
    card->setNewLocation(Card::LocationState::InOtherPlayerDeck);
    card->move(this->pos());
    return card;
}

void OtherPlayerDeckWidget::setNormalSize()
{
    this->resize(m_countOfCards * 7 + 14, 28);
}
