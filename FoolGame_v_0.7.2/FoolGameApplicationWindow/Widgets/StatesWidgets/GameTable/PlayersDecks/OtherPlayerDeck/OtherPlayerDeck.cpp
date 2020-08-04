#include "OtherPlayerDeck.h"

OtherPlayerDeck::OtherPlayerDeck(GameUserInformation* userInfo, QWidget *parent)
    :SharedPlayersDeckParent{ userInfo, parent },
     m_countOfCards{ 0 },
     m_cardShirtPixmap{ "D:/FoolGame/FoolGameDesktopClient/pictures/Cards/cardShirt.jpg" }
    {
        this->setFixedSize(90, 90);
    }

QSize OtherPlayerDeck::sizeHint() const
{
    return QSize(m_countOfCards * 7 + 14, 28);
}


void OtherPlayerDeck::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.save();
        painter.translate(this->width() / 2, this->height() * 0.4);
        painter.rotate(-30);
        qreal step = 150.0 / m_countOfCards;
        for(int i = 0; i < m_countOfCards; ++i)
        {
            painter.drawPixmap(QRect(0, 0, 30, 42), m_cardShirtPixmap);
            painter.rotate(step);
        }
    painter.restore();

    painter.setBrush(QBrush(QColor(255, 0, 0), Qt::BrushStyle::Dense3Pattern));
    switch (m_playerQueue)
    {
        case QueueMove::Attacker: painter.setPen(QPen(Qt::GlobalColor::red, 2));    break;
        case QueueMove::Other:    painter.setPen(QPen(Qt::GlobalColor::yellow, 2)); break;
        case QueueMove::Defender: painter.setPen(QPen(Qt::GlobalColor::green, 2));  break;
    }
    painter.drawRect(QRect(25, 25, this->width() - 50, this->height() - 50));

    painter.drawPixmap(QRect(25, 25, this->width() - 50, this->height() - 50), this->m_userInfo->userAvatar());
}

quint8 OtherPlayerDeck::amountOfCards() const
{
    return m_countOfCards;
}
void OtherPlayerDeck::putCard(Card* card)
{
    ++m_countOfCards;
    card->setNewLocation(Card::LocationState::InOtherPlayerDeck);
    QObject::connect(card, &Card::endOfAnimation, card, &QObject::deleteLater);
    card->doAnimationOnPoint(this->pos());
}
Card* OtherPlayerDeck::takeCard(Card::Suit cardSuit, Card::Dignity cardDignity, QWidget* cardParent)
{
    if(m_countOfCards > 0)
        --m_countOfCards;

    Card* card = new Card(cardSuit, cardDignity, cardParent);
    card->setNewLocation(Card::LocationState::InOtherPlayerDeck);
    card->move(this->pos());
    return card;
}

void OtherPlayerDeck::mousePressEvent(QMouseEvent*)
{
    QMessageBox::information(this, "User info:", QString("Name: %1\n"
                                                         "ID  : %2").arg(m_userInfo->userName()).arg(m_userInfo->userID()));
}
