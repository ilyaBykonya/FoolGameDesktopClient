#include "StartDeckWidget.h"

StartDeckWidget::StartDeckWidget(DeckSize count, Card::Suit cardSuit, Card::Dignity cardDignity, QWidget *parent)
    :QWidget{ parent },
     m_countOfCards{ count },
     m_trump{ cardSuit },
     m_firstCardPixmap{ QString("D:/FoolGame/FoolGameDesktopClient/pictures/Cards/%1_%2.png").arg(cardSuit).arg(cardDignity) },
     m_shirtCardPixmap{ "D:/FoolGame/FoolGameDesktopClient/pictures/Cards/cardShirt.jpg" },
     m_trumpPixmap(QString("D:/FoolGame/FoolGameDesktopClient/pictures/cards_suit/%1.png").arg(cardSuit))
    {
        this->setObjectName("StartDeckWidget");
        this->setFixedSize(72, 120);
    }

Card* StartDeckWidget::takeCard(Card::Suit cardSuit, Card::Dignity cardDignity, QWidget *cardParent)
{
    if(m_countOfCards > 0)
        --m_countOfCards;

    this->update();

    Card* card = new Card(cardSuit, cardDignity, cardParent);
    card->setNewLocation(Card::LocationState::InStartDeck);
    card->move(this->pos());
    return card;
}

void StartDeckWidget::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e);
    QPainter painter(this);




    //насчёт координат вопросов лучше не задавать. Так надо.
    //Правильные цифры найдены путём экспериментов.
    if(m_countOfCards > 0)
    {
        painter.save();
            painter.translate(this->width() / 2, this->height() / 2);
            painter.rotate(90);
            painter.translate(-m_firstCardPixmap.width() / 3, -m_firstCardPixmap.height() / 4);
            painter.drawPixmap(QRect(0, 0, 65, 90), m_firstCardPixmap);
        painter.restore();

        for(quint8 i = 1; i < m_countOfCards; ++i)
        {
            painter.drawPixmap(QRect((-this->width() / 3 - i / 5),
                                     (this->height() - m_shirtCardPixmap.height()) / 2 ,
                                     65, 90),
                                     m_shirtCardPixmap);
        }
    }
    else
    {
        painter.drawPixmap(QRect(5, 5, this->width() - 10, ((this->width() - 10) * m_trumpPixmap.height() / m_trumpPixmap.height())), m_trumpPixmap);
    }
}
