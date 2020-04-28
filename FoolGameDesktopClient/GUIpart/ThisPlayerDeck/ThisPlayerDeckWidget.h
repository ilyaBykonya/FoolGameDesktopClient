#ifndef THISPLAYERDECKWIDGET_H
#define THISPLAYERDECKWIDGET_H

#include <algorithm>
#include "../../GUIpart/SharedParentForPlayersDeck/SharedParentForPlayersDeck.h"


class ThisPlayerDeckWidget : public SharedParentForPlayersDeck
{
    Q_OBJECT

private:
    QList<Card*> m_playerCardsList;
    Card* m_primaryTarget;
    Card* m_secondaryTarget;
public:
    explicit ThisPlayerDeckWidget(qint16, QWidget *parent);

    QList<Card*>& getDeck() { return m_playerCardsList; };

    int amountCardsInDeck() const;
    virtual Card* takeCard(Card::Suit, Card::Dignity) override;
public slots:
    virtual void putCard(Card* card) override;

signals:
    void tryToss(Card*);
    void tryBeat(Card*);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

    void setNormalSize();
};

#endif // THISPLAYERDECKWIDGET_H
