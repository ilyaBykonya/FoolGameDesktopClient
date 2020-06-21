#ifndef THISPLAYERDECKWIDGET_H
#define THISPLAYERDECKWIDGET_H
#include "../SharedParentForPlayersDeck/SharedParentForPlayersDeck.h"
#include <algorithm>



class ThisPlayerDeckWidget : public SharedParentForPlayersDeck
{
    Q_OBJECT

private:
    QVector<Card*> m_playerCardsList;

public:
    explicit ThisPlayerDeckWidget(UserID, QWidget *parent);

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

#endif // THISPLAYERDECKWIDGET_H
