#pragma once
#include "InstanceGUIPart/GameTable/Player/ShowUserInfo/ShowUserInfoWidget.h"
#include "InstanceGUIPart/GameTable/Card/Card.h"
#include <QPushButton>

class SharedPlayersDeckParent: public QWidget
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
    ShowUserInfoWidget* m_user;

public:
    explicit SharedPlayersDeckParent(UserID, const QString&, QWidget *parent = nullptr);

    void setQueue(QueueMove);
    QueueMove queue() const;
    ShowUserInfoWidget* user();


    virtual void setNormalSize() = 0;
    virtual quint8 amountOfCards() const = 0;
    virtual void putCard(Card*) = 0;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) = 0;
};

