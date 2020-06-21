#ifndef SHAREDPARENTFORPLAYERSDECK_H
#define SHAREDPARENTFORPLAYERSDECK_H
#include "../Card/Card.h"

class SharedParentForPlayersDeck: public QWidget
{
    Q_OBJECT
public:
    enum QueueMove
    {
        Attacker = 0,
        Defender = 1,
        Other = 2
    };
protected:
    QueueMove m_playerQueue;
    UserID m_ID;

public:
    explicit SharedParentForPlayersDeck(UserID, QWidget *parent = nullptr);

    void setQueue(QueueMove);
    QueueMove queue() const;

    UserID id() const;
    virtual void setNormalSize() = 0;
    virtual quint8 amountOfCards() const = 0;
    virtual void putCard(Card*) = 0;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) = 0;
};

#endif // SHAREDPARENTFORPLAYERSDECK_H
