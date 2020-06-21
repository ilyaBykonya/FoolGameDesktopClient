#include "BattlePairWidget.h"


BattlePairWidget::BattlePairWidget(QPoint parentPos, QWidget *parent)
    :QWidget{ parent },
     m_firstCard{ nullptr },
     m_secondCard{ nullptr },
     m_pairID{ 0 },
     m_parentPosition{ parentPos },
     m_graphicsEffect{ new QGraphicsDropShadowEffect(this) }
    {
        m_graphicsEffect->setBlurRadius(25);
        m_graphicsEffect->setOffset(0, 0);
        setPairState(PairState::Empty);
        setTargetState(TargetState::NotTarget);
        this->setGraphicsEffect(m_graphicsEffect);
        this->setFixedSize(55, 100);
    }
BattlePairWidget::~BattlePairWidget()
{
    this->hide();
}



QSize BattlePairWidget::sizeHint() const
{
    return size() * 1.1;
}

PairID BattlePairWidget::pairID() const
{
    return m_pairID;
}
Card* BattlePairWidget::firstCard()
{
    return m_firstCard;
}
Card* BattlePairWidget::secondCard()
{
    return m_secondCard;
}

BattlePairWidget::PairState BattlePairWidget::state() const
{
    return m_pairState;
}
void BattlePairWidget::setTargetState(TargetState newTargetState)
{
    m_pairTarget = newTargetState;
    (m_pairTarget == TargetState::Target) ? (m_graphicsEffect->setEnabled(true)) : (m_graphicsEffect->setEnabled(false));
    this->update();
}




void BattlePairWidget::tossOnThisPair(Card* card)
{
    if(card == nullptr)
        return;
    if(m_pairState != PairState::Empty)
        return;

    this->m_pairID = (((card->suit() + 1) * 100) + card->dignity());

    m_firstCard = card;
    this->m_pairState = PairState::NotBeaten;
    card->setNewLocation(Card::LocationState::InBattlePlace);
    QObject::connect(card, &Card::endOfAnimation, this, &BattlePairWidget::tossOnThisPairSecondStep, Qt::ConnectionType::UniqueConnection);
    card->doAnimationOnPoint(this->pos() + m_parentPosition);
}
void BattlePairWidget::tossOnThisPairSecondStep(Card*)
{
    QObject::disconnect(m_firstCard, &Card::endOfAnimation, this, &BattlePairWidget::tossOnThisPairSecondStep);
    m_firstCard->hide();
    this->update();
}

void BattlePairWidget::beatThisPair(Card* card)
{
    if(card == nullptr)
        return;
    if(m_pairState != PairState::NotBeaten)
        return;
    m_secondCard = card;
    this->m_pairState = PairState::Beaten;
    card->setNewLocation(Card::LocationState::InBattlePlace);
    QObject::connect(card, &Card::endOfAnimation, this, &BattlePairWidget::beatThisPairSecondStep, Qt::ConnectionType::UniqueConnection);
    card->doAnimationOnPoint(this->pos() + m_parentPosition);
}
void BattlePairWidget::beatThisPairSecondStep(Card*)
{
    QObject::disconnect(m_secondCard, &Card::endOfAnimation, this, &BattlePairWidget::beatThisPairSecondStep);
    m_secondCard->hide();
    this->update();
}





void BattlePairWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    switch (m_pairState)
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

}
void BattlePairWidget::setPairState(PairState newPairState)
{
    m_pairState = newPairState;
    switch (m_pairState)
    {
        case PairState::Empty     :    m_graphicsEffect->setColor(QColor(255, 0, 0)); break;
        case PairState::Beaten    :    m_graphicsEffect->setColor(QColor(0, 255, 255)); break;
        case PairState::NotBeaten :    m_graphicsEffect->setColor(QColor(0, 255, 0)); break;
    }
}
