#include "BattlePairWidget.h"


BattlePairWidget::BattlePairWidget(QPoint parentPos, QWidget *parent)
    :QWidget{ parent },
     m_firstCard{ nullptr },
     m_secondCard{ nullptr },
     m_pairID{ 0 },
     m_parentPosition{ parentPos },
     m_graphicsEffect{ new QGraphicsDropShadowEffect(this) },
     m_shadowColor{ Qt::GlobalColor::blue }
    {
        m_graphicsEffect->setBlurRadius(25);
        m_graphicsEffect->setOffset(0, 0);
        setPairState(PairState::Empty);
        setTargetState(TargetState::NotTarget);
        this->setGraphicsEffect(m_graphicsEffect);
        this->setFixedSize(67, 130);
    }

BattlePairWidget::~BattlePairWidget()
{
    this->hide();
}
QSize BattlePairWidget::sizeHint() const
{
    return size();
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
void BattlePairWidget::setTargetState(TargetState newTargetState)
{
    m_pairTarget = newTargetState;
    if(m_pairTarget == TargetState::Target)
    {
        m_graphicsEffect->setEnabled(true);
        m_graphicsEffect->setColor(m_shadowColor);
    }
    else
    {
        m_graphicsEffect->setEnabled(false);
    }
    this->update();
}



void BattlePairWidget::setPairState(PairState newPairState)
{
    m_pairState = newPairState;
    switch (m_pairState)
    {
        case PairState::Empty     :
        {
            m_shadowColor = QColor(0, 0, 255);
            break;
        }
        case PairState::Beaten    :
        {
            m_shadowColor = QColor(255, 0, 0);
            break;
        }
        case PairState::NotBeaten :
        {
            m_shadowColor = QColor(0, 255, 0);
            break;
        }
    }
    m_graphicsEffect->setColor(m_shadowColor);
    m_graphicsEffect->update();
}
BattlePairWidget::PairState BattlePairWidget::state() const
{
    return m_pairState;
}



void BattlePairWidget::tossOnThisPair(Card* card)
{
    if(card == nullptr)
        return;
    if(m_pairState != PairState::Empty)
        return;

    this->m_pairID = (((card->suit() + 1) * 100) + card->dignity());

    m_firstCard = card;
    this->setPairState(PairState::NotBeaten);
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
    this->setPairState(PairState::Beaten);
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
        painter.drawPixmap(QRect(1, 2, 65, 90), m_firstCard->getPixmapForPrint());
    if(m_secondCard)
        painter.drawPixmap(QRect(1, 38, 65, 90), m_secondCard->getPixmapForPrint());

}


