#ifndef OTHERPLAYERDECKWIDGET_H
#define OTHERPLAYERDECKWIDGET_H

#include <QPainter>
#include "../../GUIpart/SharedParentForPlayersDeck/SharedParentForPlayersDeck.h"

class OtherPlayerDeckWidget: public SharedParentForPlayersDeck
{
    Q_OBJECT
private:
    int m_countOfCards;
public:
    explicit OtherPlayerDeckWidget(qint16, QWidget *parent = nullptr);
    int countOfCards() const { return m_countOfCards; }
    virtual Card* takeCard(Card::Suit, Card::Dignity) override;

public slots:
    virtual void putCard(Card* card) override;

protected:
    void setNormalSize();
    virtual void paintEvent(QPaintEvent*) override;
};
#endif // OTHERPLAYERDECKWIDGET_H
