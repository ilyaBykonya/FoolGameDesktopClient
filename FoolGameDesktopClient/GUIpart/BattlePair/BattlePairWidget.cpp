#include "BattlePairWidget.h"


BattlePairWidget::BattlePairWidget(Card* card, QWidget *parent)
    :QWidget{ parent },
     m_firstCard{ card },
     m_secondCard{ nullptr },
     m_state{ NotBeaten }
    {
        card->setNewLocation(Card::LocationState::InBattlePlace);
        this->setFixedSize(card->getPixmapForPrint().width() + 6, card->getPixmapForPrint().height() * 1.4);
        m_ID = (((static_cast<qint16>(card->suit()) + 1) * 10) + static_cast<qint16>(card->dignity()));
    }

BattlePairWidget::~BattlePairWidget()
{
    this->hide();
}

void BattlePairWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    switch (m_state)
    {
        case PairState::Beaten    :    painter.setBrush(QBrush(QColor(0, 255, 0), Qt::BrushStyle::Dense3Pattern)); break;
        case PairState::NotBeaten :    painter.setBrush(QBrush(QColor(255, 255, 0), Qt::BrushStyle::Dense3Pattern)); break;
    }

    painter.drawRect(this->rect());

    if(m_firstCard != nullptr)
        painter.drawPixmap(QRect{ QPoint{3, 0}, m_firstCard->getPixmapForPrint().size()}, m_firstCard->getPixmapForPrint());
    if(m_secondCard != nullptr)
        painter.drawPixmap(QRect{ QPoint{3, int(this->height() * 0.35)}, m_secondCard->getPixmapForPrint().size()}, m_secondCard->getPixmapForPrint());
}

void BattlePairWidget::mousePressEvent(QMouseEvent*)
{
    if(this->m_state == PairState::NotBeaten)
        emit clickToThisPair(this);
}

void BattlePairWidget::beatThisPair(Card* card)
{
    if(card == nullptr)
        return;

    m_secondCard = card;
    this->repaint();
}

