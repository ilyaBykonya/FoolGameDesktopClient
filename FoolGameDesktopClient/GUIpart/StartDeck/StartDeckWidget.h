#ifndef STARTDECKWIDGET_H
#define STARTDECKWIDGET_H

#include <QWidget>
#include "../../Card/Card.h"

class StartDeckWidget : public QWidget
{
    Q_OBJECT
private:
    int m_countOfCards;
    QPixmap m_firstCardPixmap;
    QPixmap m_shirtCardPixmap;

public:
    explicit StartDeckWidget(int, Card::Dignity, Card::Suit, QWidget *parent);
    Card* takeCard(Card::Suit, Card::Dignity);

protected:
    virtual void paintEvent(QPaintEvent*) override;
};

#endif // STARTDECKWIDGET_H
