#include "BattlePairWidget.h"


BattlePairWidget::BattlePairWidget(QPoint parentPos, QWidget *parent)
    :QWidget{ parent },
     m_firstCard{ nullptr },
     m_secondCard{ nullptr },
     m_state{ Empty },
     m_ID{ 0 },
     m_parentPosition{ parentPos }
    {
        this->setFixedSize(55, 100);
    }


void BattlePairWidget::tossOnThisPair(Card* card)
{
    if(card == nullptr)
        return;

    card->setNewLocation(Card::LocationState::InBattlePlace);
    card->show();
    QObject::connect(card, &Card::endOfAnimation, this, &BattlePairWidget::tossOnThisPairSecondStep, Qt::ConnectionType::UniqueConnection);
    card->doAnimationOnPoint(this->pos() + m_parentPosition);
}
void BattlePairWidget::tossOnThisPairSecondStep(Card* card)
{
    this->m_ID = (((card->suit() + 1) * 100) + card->dignity());
    m_firstCard = card;
    QObject::disconnect(m_firstCard, &Card::endOfAnimation, this, &BattlePairWidget::tossOnThisPairSecondStep);
    this->m_state = PairState::NotBeaten;
    m_firstCard->hide();
    this->repaint();
}


void BattlePairWidget::beatThisPair(Card* card)
{
    if(card == nullptr)
        return;

    card->setNewLocation(Card::LocationState::InBattlePlace);
    card->show();
    QObject::connect(card, &Card::endOfAnimation, this, &BattlePairWidget::beatThisPairSecondStep, Qt::ConnectionType::UniqueConnection);
    card->doAnimationOnPoint(this->pos() + m_parentPosition);
}
void BattlePairWidget::beatThisPairSecondStep(Card* card)
{
    m_secondCard = card;
    QObject::disconnect(m_secondCard, &Card::endOfAnimation, this, &BattlePairWidget::beatThisPairSecondStep);
    this->m_state = PairState::Beaten;
    m_secondCard->hide();
    this->repaint();
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
        painter.drawPixmap(QRect(3, 0, 50, 70), m_firstCard->getPixmapForPrint());
    if(m_secondCard)
        painter.drawPixmap(QRect(3, this->height() * 0.4, 50, 70), m_secondCard->getPixmapForPrint());
}
