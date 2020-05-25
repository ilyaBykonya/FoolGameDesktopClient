#ifndef SHAREDPARENTFORPLAYERSDECK_H
#define SHAREDPARENTFORPLAYERSDECK_H

#include <QWidget>
#include "../Card/SharedOptions.h"
#include "../Card/Card.h"
class SharedParentForPlayersDeck : public QWidget
{
    Q_OBJECT
protected:
    QueueMove m_playerQueue;
    qint16 m_ID;
public:
    explicit SharedParentForPlayersDeck(qint16, QWidget *parent = nullptr);

    void setQueue(QueueMove);
    QueueMove queue() const;

    qint16 id() const;
    virtual void putCard(Card*) = 0;
    virtual Card* takeCard(Card::Suit, Card::Dignity, QWidget*) = 0;
};

#endif // SHAREDPARENTFORPLAYERSDECK_H
