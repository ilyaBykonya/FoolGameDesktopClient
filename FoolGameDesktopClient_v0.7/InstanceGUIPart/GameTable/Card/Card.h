#ifndef CARD_H
#define CARD_H
#include <cmath>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "../../../TypesAliases.h"

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
    static bool less(const Card*, const Card*);

protected:
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
