#include "BattlePairWidget.h"


BattlePairWidget::BattlePairWidget(Card* card, QWidget *parent)
    :QWidget{ parent },
     m_firstCard{ nullptr },
     m_secondCard{ nullptr },
     m_state{ NotBeaten }
    {
        this->setObjectName("BattlePairWidget");
        this->setFixedSize(card->getPixmapForPrint().width() + 6, card->getPixmapForPrint().height() * 1.4);
        m_ID = (((static_cast<qint16>(card->suit()) + 1) * 10) + static_cast<qint16>(card->dignity()));
        card->setNewLocation(Card::LocationState::InBattlePlace);
        QObject::connect(card, &Card::endOfAnimation, this, &BattlePairWidget::secondPartOfConstructor);
    }


void BattlePairWidget::secondPartOfConstructor(Card* card)
{
    card->setNewLocation(Card::LocationState::InBattlePlace);
    QObject::disconnect(card, &Card::endOfAnimation, this, &BattlePairWidget::secondPartOfConstructor);
    card->hide();
    m_firstCard = card;
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
        case PairState::Beaten    :    painter.setBrush(QBrush(QColor(0, 255, 0), Qt::BrushStyle::Dense3Pattern)); break;
        case PairState::NotBeaten :    painter.setBrush(QBrush(QColor(255, 255, 0), Qt::BrushStyle::Dense3Pattern)); break;
    }

    painter.drawRect(this->rect());
    if(m_firstCard)
        painter.drawPixmap(QRect(3, 0, 50, 70), m_firstCard->getPixmapForPrint());
    if(m_secondCard)
        painter.drawPixmap(QRect(3, 25, 50, 70), m_secondCard->getPixmapForPrint());
}

void BattlePairWidget::beatThisPair(Card* card)
{
    if(card == nullptr)
        return;
    this->m_state = PairState::Beaten;
    m_secondCard = card;
    card->setNewLocation(Card::LocationState::InBattlePlace);
    QObject::connect(m_secondCard, &Card::endOfAnimation, this, &BattlePairWidget::beatThisPairSecondStep);
}
void BattlePairWidget::beatThisPairSecondStep(Card* card)
{
    QObject::disconnect(card, &Card::endOfAnimation, this, &BattlePairWidget::beatThisPairSecondStep);
    card->hide();

    this->repaint();
}
