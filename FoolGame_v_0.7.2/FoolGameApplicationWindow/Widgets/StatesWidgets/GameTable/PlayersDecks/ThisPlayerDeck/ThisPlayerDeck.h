#pragma once
#include "FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/PlayersDecks/SharedParentForPlayersDeck/SharedParentForPlayersDeck.h"
#include <algorithm>


class ThisPlayerDeck : public SharedPlayersDeckParent
{
    Q_OBJECT

private:
    QVector<Card*> m_playerCardsList;

public:
    explicit ThisPlayerDeck(GameUserInformation*, QWidget *parent);

    QVector<Card*>& getDeck() { return m_playerCardsList; };

    virtual quint8 amountOfCards() const override;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) override;

public slots:
    virtual void putCard(Card*) override;

protected slots:
    virtual void paintEvent(QPaintEvent *) override;
    void setNormalSize();
};

