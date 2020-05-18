#include "ThisPlayerDeckWidget.h"

ThisPlayerDeckWidget::ThisPlayerDeckWidget(qint16 id, QWidget *parent)
    :SharedParentForPlayersDeck{ id, parent },
     m_primaryTarget{ nullptr },
     m_secondaryTarget{ nullptr }
    {
        this->setObjectName("ThisPlayerDeckWidget");
        this->setMouseTracking(true);
        this->setFixedHeight(110);
    }


void ThisPlayerDeckWidget::setNormalSize(Card* card)
{
    int weight = 50 * m_playerCardsList.size() + 60;
    this->resize(weight, this->height());
    qint16 i = 0;

    for(auto it = m_playerCardsList.begin(); (i < m_playerCardsList.size()) && (it != m_playerCardsList.end()); ++i, ++it)
    {
        (*it)->moveThisCard(this->pos() + QPoint(i * 50 + 10, 40));

        (*it)->repaint();
    }
    this->repaint();
}


void ThisPlayerDeckWidget::putCard(Card* card)
{
    if(card == nullptr)
        return;

    card->setNewLocation(Card::LocationState::InPlayerDeck);
    card->show();
    QObject::connect(card, &Card::endOfAnimation, this, &ThisPlayerDeckWidget::setNormalSize);
    m_playerCardsList.push_back(card);
    std::sort(m_playerCardsList.begin(), m_playerCardsList.end(), &Card::less);
    card->doAnimationOnPoint(this->pos());
}

Card* ThisPlayerDeckWidget::takeCard(Card::Suit s, Card::Dignity d, QWidget*)
{
    for(auto card = m_playerCardsList.begin(); card != m_playerCardsList.end(); ++card)
    {
        if(((*card)->suit() == s) && ((*card)->dignity() == d))
        {
            Card* buf = (*card);
            QObject::disconnect(buf, &Card::endOfAnimation, this, &ThisPlayerDeckWidget::setNormalSize);
            m_playerCardsList.erase(card);
            this->setNormalSize(nullptr);
            m_primaryTarget = nullptr;
            m_secondaryTarget = nullptr;
            setMouseTracking(true);
            this->repaint();
            return buf;
        }
    }
    return nullptr;
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
}


