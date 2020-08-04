#pragma once
#include "FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/PlayersDecks/SharedParentForPlayersDeck/SharedParentForPlayersDeck.h"
#include <QVBoxLayout>
class OtherPlayerDeck: public SharedPlayersDeckParent
{
    Q_OBJECT
private:
    quint8 m_countOfCards;
    QPixmap m_cardShirtPixmap;

public:
    explicit OtherPlayerDeck(GameUserInformation*, QWidget *parent = nullptr);

    virtual quint8 amountOfCards() const override;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) override;

    virtual QSize sizeHint() const override;
public slots:
    virtual void putCard(Card* card) override;

protected slots:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
};

