#ifndef CARD_H
#define CARD_H
#include "FoolGameApplicationWindow/Files/TypesAliases.h"
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <cmath>

class Card: public QWidget
{
    Q_OBJECT
public:
    enum Suit
    {
        Heart,//черва
        Spade,//пика
        Diamond,//бубна
        Club,//трефа(крести)
        MAX_SUIT
    };
    enum Dignity
    {
        two = 0,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        lady,
        king,
        ace,
        MAX_DIGNITY
    };
    enum LocationState
    {
        InStartDeck,
        InPlayerDeck ,
        InBattlePlace,
        InHangUp,
        InUserHand,
        InOtherPlayerDeck
    };

private:
    Dignity m_dignity;
    Suit m_suit;

    QPixmap m_pictureCard;
    QPixmap m_shirtCard;

    LocationState m_location;

    //для перетаскиваний
    QPoint m_lastClick;

public:
    Card(Suit, Dignity, QWidget*);
    Card(const Card&) = delete;
    Card(Card&&) = delete;

    Dignity dignity() const;
    Suit suit() const;

    LocationState location() const;
    void setNewLocation(LocationState);

    const QPixmap& getPixmapForPrint();

    //для сортировки карт в колоде игрока
    static bool less(const Card*, const Card*);

protected slots:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void paintEvent(QPaintEvent *event) override;

public slots:
    void doAnimationOnPoint(QPoint);

signals:
    void dragThisElement(Card*);
    void movingThisElement(Card*, QPoint);
    void dropThisElement(Card*, QPoint);

    void endOfAnimation(Card*);
};

#endif // CARD_H
