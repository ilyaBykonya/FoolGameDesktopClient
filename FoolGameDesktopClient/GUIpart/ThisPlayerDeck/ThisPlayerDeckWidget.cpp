#include "ThisPlayerDeckWidget.h"

ThisPlayerDeckWidget::ThisPlayerDeckWidget(qint16 id, QWidget *parent)
    :SharedParentForPlayersDeck{ id, parent },
     m_primaryTarget{ nullptr },
     m_secondaryTarget{ nullptr }
    {
        this->setMouseTracking(true);
        this->setFixedHeight(110);
    }


void ThisPlayerDeckWidget::setNormalSize()
{
    int weight = 20 * m_playerCardsList.size() + 30;
    this->resize(weight, this->height());
    this->repaint();
}

void ThisPlayerDeckWidget::putCard(Card* card)
{
    if(card == nullptr)
        return;

    card->setNewLocation(Card::LocationState::InPlayerDeck);
    m_playerCardsList.push_back(card);
    std::sort(m_playerCardsList.begin(), m_playerCardsList.end());

    this->setNormalSize();
}
Card* ThisPlayerDeckWidget::takeCard(Card::Suit s, Card::Dignity d)
{
    for(auto card = m_playerCardsList.begin(); card != m_playerCardsList.end(); ++card)
    {
        if(((*card)->suit() == s) && ((*card)->dignity() == d))
        {
            Card* buf = (*card);
            m_playerCardsList.erase(card);
            this->setNormalSize();
            m_primaryTarget = nullptr;
            m_secondaryTarget = nullptr;
            setMouseTracking(true);
            return buf;
        }
    }
    return nullptr;
}

int ThisPlayerDeckWidget::amountCardsInDeck() const
{
    return m_playerCardsList.size();
}

void ThisPlayerDeckWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(Qt::GlobalColor::black));
        painter.drawRect(rect());

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

        int i = 0;
        for(auto elem = m_playerCardsList.begin(); elem != m_playerCardsList.end(); ++elem, ++i)
        {
            if((*elem) == m_secondaryTarget)
                painter.drawPixmap(QRect(i * 20, 0, 50, 70), (*elem)->getPixmapForPrint());
            else if((*elem) == m_primaryTarget)
                painter.drawPixmap(QRect(i * 20, 20, 50, 70), (*elem)->getPixmapForPrint());
            else
                painter.drawPixmap(QRect(i * 20, 40, 50, 70), (*elem)->getPixmapForPrint());
        }

}

void ThisPlayerDeckWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(m_playerCardsList.isEmpty() || (m_secondaryTarget != nullptr))
       return;


    int xPos = event->x();

    /*Заменить конструкцию ниже на
     *auto it = m_playerCardsList.begin();
     *  for(int i = 0; i < (xPos / 20) - 1; ++i)
     *     this->m_primaryTarget = (*it);
     *Возможно, что даже не крашнется
    */
    auto it = m_playerCardsList.begin();
    for(int i = 0; i < xPos / 20; ++i)
        ++it;



    if(xPos / 20 >= m_playerCardsList.size())
        m_primaryTarget = m_playerCardsList.back();
    //======================================================
    this->repaint();
}
void ThisPlayerDeckWidget::mousePressEvent(QMouseEvent* event)
{
    if(m_primaryTarget == nullptr)
        return;

    if(event->button() == Qt::MouseButton::RightButton)
    {
        m_primaryTarget = nullptr;
        m_secondaryTarget = nullptr;
        setMouseTracking(true);
        this->repaint();
    }

    this->setNormalSize();
    this->m_secondaryTarget = this->m_primaryTarget;
    this->setMouseTracking(false);

    if(m_playerQueue == QueueMove::Defender) {
        emit tryBeat(m_secondaryTarget);
    } else {
        emit tryToss(m_secondaryTarget);
    }

    this->repaint();
}
void ThisPlayerDeckWidget::leaveEvent(QEvent*)
{
    if(m_secondaryTarget != nullptr)
        return;

    m_primaryTarget = nullptr;
    this->repaint();
}



