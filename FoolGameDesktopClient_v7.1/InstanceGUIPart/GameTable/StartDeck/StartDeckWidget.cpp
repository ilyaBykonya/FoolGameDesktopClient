#include "StartDeckWidget.h"

StartDeckWidget::StartDeckWidget(quint8 count, Card::Suit cardSuit, Card::Dignity cardDignity, QWidget *parent)
    :QWidget{ parent },
     m_countOfCards{ count },
     m_trump{ cardSuit },
//     m_firstCardPixmap{ QString("D:/FoolGame/FoolGameDesktopClient/pictures/Cards/%1_%2.png").arg(cardSuit).arg(cardDignity) },
//     m_shirtCardPixmap{ "D:/FoolGame/FoolGameDesktopClient/pictures/Cards/cardShirt.jpg" },
//     m_trumpPixmap(QString("D:/FoolGame/FoolGameDesktopClient/pictures/cards_suit/%1.png").arg(cardSuit))
     m_firstCardPixmap{ QString("../pictures/Cards/%1_%2.png").arg(cardSuit).arg(cardDignity) },
     m_shirtCardPixmap{ "../pictures/Cards/cardShirt.jpg" },
     m_trumpPixmap(QString("../pictures/cards_suit/%1.png").arg(cardSuit))
    {
        this->setFixedSize(50, 100);
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

void StartDeckWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(0, 255, 0), Qt::BrushStyle::Dense3Pattern));
    painter.drawRect(this->rect());

    //насчёт координат вопросов не задавай. Так надо. Координаты рисования вычисялются относительно картинки.
    //Сказано тупо, но суть такая - при повороте там полная Ж
    if(m_countOfCards > 0)
    {
        painter.rotate(90);
        painter.drawPixmap(QRect((this->height() / 2 - m_firstCardPixmap.width() / 2),
                                 (-this->width() * 0.6 - m_firstCardPixmap.width() * 0.4),
                                 50, 70),
                                 m_firstCardPixmap);
        painter.rotate(-90);

        for(quint8 i = 1; i < m_countOfCards; ++i)
        {
            painter.drawPixmap(QRect((-this->width() / 3 - i / 5),
                                     (this->height() - m_shirtCardPixmap.height()) / 2 ,
                                     50, 70),
                                     m_shirtCardPixmap);
        }
    }
    else
    {

        painter.drawPixmap(QRect(5, ((this->height() / 2) - (this->width() / 2)), this->width() - 10, (this->height() / 2)), m_trumpPixmap);
    }
}
