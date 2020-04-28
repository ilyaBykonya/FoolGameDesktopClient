#include "StartDeckWidget.h"

StartDeckWidget::StartDeckWidget(int count, Card::Dignity d, Card::Suit s, QWidget *parent)
    :QWidget{ parent },
     m_countOfCards{ count },
     m_firstCardPixmap{ "D:/C++/codes/QtProjects/CardGame/cards/" + QString::number(s) + "_" + QString::number(d) + ".png" },
     m_shirtCardPixmap{ "D:/C++/codes/QtProjects/CardGame/cards/cardShirt.jpg" }
    {
        this->setFixedSize(50, 100);
    }

Card* StartDeckWidget::takeCard(Card::Suit s, Card::Dignity d)
{
    --m_countOfCards;
    this->repaint();
    return (new Card(s, d, this->parent()));
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
                                 m_firstCardPixmap.width(), m_firstCardPixmap.height()),
                                 m_firstCardPixmap);
        painter.rotate(-90);

        for(int i = 1; i < m_countOfCards; ++i)
        {
            painter.drawPixmap(QRect((-this->width() / 6 - i / 5),
                                     (this->height() - m_shirtCardPixmap.height()) / 2 ,
                                     m_shirtCardPixmap.width(), m_shirtCardPixmap.height()),
                                     m_shirtCardPixmap);
        }
    }
}
