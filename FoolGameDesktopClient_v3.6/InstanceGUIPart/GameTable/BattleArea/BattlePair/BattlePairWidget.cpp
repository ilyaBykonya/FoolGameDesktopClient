#include "BattlePairWidget.h"


BattlePairWidget::BattlePairWidget(QPoint parentPos, QWidget *parent)
    :QWidget{ parent },
     m_firstCard{ nullptr },
     m_secondCard{ nullptr },
     m_state{ Empty },
     m_targetState{ NotTarget },
     m_ID{ 0 },
     m_parentPosition{ parentPos }
    {
        this->setFixedSize(55, 100);
    }


void BattlePairWidget::tossOnThisPair(Card* card)
{
    if(card == nullptr)
        return;

    m_firstCard = card;
    this->m_ID = (((card->suit() + 1) * 100) + card->dignity());
    this->m_state = PairState::NotBeaten;
    card->setNewLocation(Card::LocationState::InBattlePlace);
    card->show();
    QObject::connect(card, &Card::endOfAnimation, this, &BattlePairWidget::tossOnThisPairSecondStep, Qt::ConnectionType::UniqueConnection);
    card->doAnimationOnPoint(this->pos() + m_parentPosition);
}
void BattlePairWidget::tossOnThisPairSecondStep(Card* card)
{
    if(m_firstCard)
    {
        QObject::disconnect(m_firstCard, &Card::endOfAnimation, this, &BattlePairWidget::tossOnThisPairSecondStep);
        m_firstCard->hide();
    }
    else
    {
        if(card)
        {
            m_firstCard = card;
            QObject::disconnect(m_firstCard, &Card::endOfAnimation, this, &BattlePairWidget::tossOnThisPairSecondStep);
            m_firstCard->hide();
        }
    }
    this->repaint();
}
Card* BattlePairWidget::cancelToss()
{
    m_ID = 0;
    Card* buf = m_firstCard;
    m_firstCard = nullptr;
    this->m_state = PairState::Empty;
    this->update();
    return buf;
}

void BattlePairWidget::beatThisPair(Card* card)
{
    if(card == nullptr)
        return;

    m_secondCard = card;
    this->m_state = PairState::Beaten;
    card->setNewLocation(Card::LocationState::InBattlePlace);
    card->show();
    QObject::connect(card, &Card::endOfAnimation, this, &BattlePairWidget::beatThisPairSecondStep, Qt::ConnectionType::UniqueConnection);
    card->doAnimationOnPoint(this->pos() + m_parentPosition);
}
void BattlePairWidget::beatThisPairSecondStep(Card* card)
{
    if(m_secondCard)
    {
        QObject::disconnect(m_secondCard, &Card::endOfAnimation, this, &BattlePairWidget::beatThisPairSecondStep);
        m_secondCard->hide();
    }
    this->repaint();
}
Card* BattlePairWidget::cancelBeat()
{
    Card* buf = m_secondCard;
    m_secondCard = nullptr;
    this->m_state = PairState::NotBeaten;
    this->update();
    return buf;
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
        case PairState::Empty     :    painter.setBrush(QBrush(QColor(255, 0, 0),   Qt::BrushStyle::Dense3Pattern)); break;
        case PairState::Beaten    :    painter.setBrush(QBrush(QColor(0, 255, 0),   Qt::BrushStyle::Dense3Pattern)); break;
        case PairState::NotBeaten :    painter.setBrush(QBrush(QColor(255, 255, 0), Qt::BrushStyle::Dense3Pattern)); break;
    }

    painter.drawRect(this->rect());
    if(m_firstCard)
        painter.drawPixmap(QRect(3, 0, this->width() - 6, this->height() * 0.6), m_firstCard->getPixmapForPrint());
    if(m_secondCard)
        painter.drawPixmap(QRect(3, this->height() * 0.4, this->width() - 6, this->height() * 0.6), m_secondCard->getPixmapForPrint());

    if(m_targetState == TargetState::Target)
    {
        painter.setBrush(Qt::BrushStyle::NoBrush);
        switch (m_state)
        {
            case PairState::Empty     :    painter.setPen(QPen(QColor(0, 191, 255), 3)); break;
            case PairState::Beaten    :    painter.setPen(QPen(QColor(255, 0, 0), 3)); break;
            case PairState::NotBeaten :    painter.setPen(QPen(QColor(0, 255, 0), 3)); break;
        }

        QPolygon frameLine;
        frameLine << QPoint(this->width() - 1, 1)
                  << QPoint(this->width() - 1, this->height() - 1)
                  << QPoint(1, this->height() - 1);
        painter.drawPolyline(frameLine);
    }
}
