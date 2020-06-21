#ifndef OTHERPLAYERDECKWIDGET_H
#define OTHERPLAYERDECKWIDGET_H
#include "../SharedParentForPlayersDeck/SharedParentForPlayersDeck.h"

class OtherPlayerDeckWidget: public SharedParentForPlayersDeck
{
    Q_OBJECT
private:
    quint8 m_countOfCards;
    QPixmap m_cardShirtPixmap;

public:
    explicit OtherPlayerDeckWidget(UserID, QWidget *parent = nullptr);

    virtual quint8 amountOfCards() const override;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) override;

public slots:
    virtual void putCard(Card* card) override;

protected:
    virtual void setNormalSize() override;
    virtual void paintEvent(QPaintEvent*) override;
};
#endif // OTHERPLAYERDECKWIDGET_H
