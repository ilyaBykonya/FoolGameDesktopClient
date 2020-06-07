#include "StartDeckWidget.h"

StartDeckWidget::StartDeckWidget(int count, Card::Suit s, Card::Dignity d, QWidget *parent)
    :QWidget{ parent },
     m_countOfCards{ count },
     m_firstCardPixmap{ "D:/FoolGame/FoolGameDesktopClient/pictures/Cards/" + QString::number(s) + "_" + QString::number(d) + ".png" },
     m_shirtCardPixmap{ "D:/FoolGame/FoolGameDesktopClient/pictures/Cards/cardShirt.jpg" }
    {
        this->setObjectName("StartDeckWidget");
        this->setFixedSize(50, 100);
    }

Card* StartDeckWidget::takeCard(Card::Suit s, Card::Dignity d, QWidget *cardParent)
{
    --m_countOfCards;
    if(m_countOfCards < 0)
        m_countOfCards = 0;
    this->repaint();
    Card* card = new Card(s, d, cardParent);
    card->setNewLocation(Card::LocationState::InStartDeck);
    card->moveThisCard(this->pos());
    card->show();
    qDebug() << "Take card " << m_countOfCards;
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

        for(int i = 1; i < m_countOfCards; ++i)
        {
            painter.drawPixmap(QRect((-this->width() / 6 - i / 5),
                                     (this->height() - m_shirtCardPixmap.height()) / 2 ,
                                     50, 70),
                                     m_shirtCardPixmap);
        }
    }
}
