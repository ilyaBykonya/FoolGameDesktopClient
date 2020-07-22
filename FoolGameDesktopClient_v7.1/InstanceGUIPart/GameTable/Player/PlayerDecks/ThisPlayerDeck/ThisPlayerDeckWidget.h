#pragma once
#include "../SharedParentForPlayersDeck/SharedPlayersDeckParent.h"
#include <algorithm>


class ThisPlayerDeckWidget : public SharedPlayersDeckParent
{
    Q_OBJECT

private:
    QVector<Card*> m_playerCardsList;

public:
    explicit ThisPlayerDeckWidget(UserID, const QString&, QWidget *parent);

    QVector<Card*>& getDeck() { return m_playerCardsList; };

    virtual quint8 amountOfCards() const override;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) override;

public slots:
    virtual void putCard(Card*) override;

protected:
    virtual void paintEvent(QPaintEvent *) override;

protected slots:
    virtual void setNormalSize() override;
};
