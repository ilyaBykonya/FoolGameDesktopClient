#include "OtherPlayerDeckWidget.h"

OtherPlayerDeckWidget::OtherPlayerDeckWidget(qint16 id, QWidget *parent)
    :SharedParentForPlayersDeck{ id, parent },
     m_countOfCards{ 0 }
    {
        this->setNormalSize();
    }

void OtherPlayerDeckWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(255, 0, 0), Qt::BrushStyle::Dense3Pattern));
    painter.drawRect(this->rect());

    switch (m_playerQueue)
    {
        case QueueMove::Attacker: painter.setPen(QPen(Qt::GlobalColor::red, 2));    break;
        case QueueMove::Other:    painter.setPen(QPen(Qt::GlobalColor::yellow, 2)); break;
        case QueueMove::Defender: painter.setPen(QPen(Qt::GlobalColor::green, 2));  break;
    }
    QPolygon frameLine;
    frameLine << QPoint(1, 1) << QPoint(this->width() - 1, 1)
                        << QPoint(this->width() - 1, this->height() - 1)
                        << QPoint(1, this->height() - 1);
    painter.drawPolygon(frameLine);

    QPixmap pix("D:\\FoolGame\\FoolGameDesktopClient\\pictures\\Cards\\cardShirt.jpg");
    for(int i = 0; i < m_countOfCards; ++i)
        painter.drawPixmap(QRect({2 + i * 7, 2}, {pix.size() / 3}), pix);
}

void OtherPlayerDeckWidget::setNormalSize()
{
    this->resize(m_countOfCards * 7 + 10 + 4, 28);
}

void OtherPlayerDeckWidget::putCard(Card* card)
{
    delete card;
    ++m_countOfCards;
    this->setNormalSize();
}

Card* OtherPlayerDeckWidget::takeCard(Card::Suit s, Card::Dignity d)
{
    --m_countOfCards;
    return (new Card(s, d, this->parent()));
}
