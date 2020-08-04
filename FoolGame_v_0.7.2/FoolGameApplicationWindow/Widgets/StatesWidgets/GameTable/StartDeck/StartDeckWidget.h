#ifndef STARTDECKWIDGET_H
#define STARTDECKWIDGET_H
#include "../Card/Card.h"

class StartDeckWidget : public QWidget
{
    Q_OBJECT
private:
    DeckSize m_countOfCards;
    Card::Suit m_trump;
    QPixmap m_firstCardPixmap;
    QPixmap m_shirtCardPixmap;
    QPixmap m_trumpPixmap;

public:
    explicit StartDeckWidget(DeckSize, Card::Suit, Card::Dignity, QWidget *parent);
    Card* takeCard(Card::Suit, Card::Dignity, QWidget*);

protected:
    virtual void paintEvent(QPaintEvent*) override;
};

#endif // STARTDECKWIDGET_H
