#ifndef STARTDECKWIDGET_H
#define STARTDECKWIDGET_H

#include <QWidget>
#include "../Card/Card.h"

class StartDeckWidget : public QWidget
{
    Q_OBJECT
private:
    int m_countOfCards;
    QPixmap m_firstCardPixmap;
    QPixmap m_shirtCardPixmap;

public:
    explicit StartDeckWidget(int, Card::Suit, Card::Dignity, QWidget *parent);
    Card* takeCard(Card::Suit, Card::Dignity, QWidget*);

protected:
    virtual void paintEvent(QPaintEvent*) override;
};

#endif // STARTDECKWIDGET_H
