#pragma once
#include "../SharedParentForPlayersDeck/SharedPlayersDeckParent.h"
#include <QVBoxLayout>
class OtherPlayerDeckWidget: public SharedPlayersDeckParent
{
    Q_OBJECT
private:
    quint8 m_countOfCards;
    QPixmap m_cardShirtPixmap;

public:
    explicit OtherPlayerDeckWidget(UserID, const QString&, QWidget *parent = nullptr);

    virtual quint8 amountOfCards() const override;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) override;

    virtual QSize sizeHint() const override;
public slots:
    virtual void putCard(Card* card) override;

protected:
    virtual void setNormalSize() override;
    virtual void paintEvent(QPaintEvent*) override;

};
