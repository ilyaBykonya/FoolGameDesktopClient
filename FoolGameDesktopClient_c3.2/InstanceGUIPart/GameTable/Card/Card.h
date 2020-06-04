#ifndef CARD_H
#define CARD_H

#include <QtWidgets>

class Card: public QWidget
{
    Q_OBJECT
public:
    enum Suit
    {
        Club,//трефа(крести)
        Heart,//черва
        Tambourine,//бубна
        Peak,//пика
        MAX_SUIT
    };
    enum Dignity
    {
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
        FirstCardInStartDeck,
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

    //для интерактивности (анимации и перетаскивание)
    QPoint m_startPosition;

public:
    Card(Suit s, Dignity dig, QWidget* parent);
    Card(const Card&) = delete;
    Card(Card&&) = delete;

    Dignity dignity() const { return m_dignity; }
    Suit suit() const { return m_suit; }

    LocationState location() const { return m_location; }
    void setNewLocation(LocationState);

    const QPixmap& getPixmapForPrint();
    static bool less(const Card*, const Card*);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void paintEvent(QPaintEvent *event) override;

public slots:
    void successDrop();
    void unsuccessDrop();

    void moveThisCard(QPoint);
    void doAnimationOnPoint(QPoint);


signals:
    void dragThisElement(Card*);
    void movingThisElement(Card*, QPoint);
    void dropThisElement(Card*, QPoint);

    void endOfAnimation(Card*);
};

#endif // CARD_H
