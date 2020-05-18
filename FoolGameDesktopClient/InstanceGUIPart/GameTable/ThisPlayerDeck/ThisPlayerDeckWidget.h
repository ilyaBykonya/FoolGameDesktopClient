#ifndef THISPLAYERDECKWIDGET_H
#define THISPLAYERDECKWIDGET_H

#include <algorithm>
#include "../SharedParentForPlayersDeck/SharedParentForPlayersDeck.h"


class ThisPlayerDeckWidget : public SharedParentForPlayersDeck
{
    Q_OBJECT

private:
    QVector<Card*> m_playerCardsList;
    Card* m_primaryTarget;
    Card* m_secondaryTarget;
public:
    explicit ThisPlayerDeckWidget(qint16, QWidget *parent);

    QVector<Card*>& getDeck() { return m_playerCardsList; };

    int amountCardsInDeck() const;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) override;
public slots:
    virtual void putCard(Card* card) override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;
protected slots:
    void setNormalSize(Card*);
    //void deleteCardFromDeck(Card*);
};

#endif // THISPLAYERDECKWIDGET_H
