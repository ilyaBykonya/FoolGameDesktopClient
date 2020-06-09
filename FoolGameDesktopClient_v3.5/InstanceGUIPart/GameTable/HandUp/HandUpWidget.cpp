#include "HandUpWidget.h"

HandUpWidget::HandUpWidget(QWidget *parent)
    :QWidget{ parent },
     m_countOfCards{ 0 },
     m_shirtCardPixmap{ "D:/FoolGame/FoolGameDesktopClient/pictures/Cards/cardShirt.jpg" }
    {
        this->setObjectName("HandUpWidget");
        this->setFixedSize(50, 100);
    }

void HandUpWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(QBrush(QColor(0, 0, 255), Qt::BrushStyle::Dense3Pattern));
    painter.drawRect(this->rect());


    for(int i = 0; i < m_countOfCards; ++i)
    {
        painter.drawPixmap(QRect((this->width() / 3 + i / 5),
                                 (this->height() - m_shirtCardPixmap.height()) / 2 ,
                                 m_shirtCardPixmap.width(), m_shirtCardPixmap.height()),
                                 m_shirtCardPixmap);
    }

}

void HandUpWidget::putCard(Card* card)
{
    ++m_countOfCards;
    card->doAnimationOnPoint(this->pos());
    QObject::connect(card, &Card::endOfAnimation, card, &QWidget::hide);
    QObject::connect(card, &Card::endOfAnimation, card, &QObject::deleteLater);
    this->repaint();
}
