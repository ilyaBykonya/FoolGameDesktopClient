#pragma once
#include "FoolGameApplicationWindow/Widgets/StatesWidgets/GameTable/Card/Card.h"
#include "FoolGameApplicationWindow/Objects/UsersInformation/GameUserInformation/GameUserInformation.h"
#include <QMessageBox>
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
    GameUserInformation* m_userInfo;
    QueueMove m_playerQueue;

public:
    explicit SharedPlayersDeckParent(GameUserInformation*, QWidget* = nullptr);

    void setQueue(QueueMove);
    QueueMove queue() const;

    GameUserInformation* user() const;


    virtual quint8 amountOfCards() const = 0;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) = 0;
    virtual void putCard(Card*) = 0;
};
