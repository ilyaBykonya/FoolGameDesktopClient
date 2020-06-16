#ifndef BATTLEAREAWIDGET_H
#define BATTLEAREAWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "BattlePair/BattlePairWidget.h"



class BattleAreaWidget : public QWidget
{
    Q_OBJECT
private:
    QList<BattlePairWidget*> m_pairsList;
    QHBoxLayout* m_topLine;
    QHBoxLayout* m_bottomLine;
    Card::Suit m_trump;
    BattlePairWidget* m_targetPair;

    QPoint m_thisRealPos;
public:
    explicit BattleAreaWidget(QPoint, Card::Suit, QWidget* parent);
    qint16 countOfPairs() const { return m_pairsList.size(); }

    BattlePairWidget* addNewPair();

    BattlePairWidget* checkRightTossingCard(Card*);
    void tossCard(Card*);

    BattlePairWidget* checkRightBeatingCard(Card*, QPoint);
    void beatCard(Card*, qint16);

    BattlePairWidget* checkRightTrancferableCard(Card*);
    void trancferableCard(Card*);


    QList<Card*> endOfMove();

    BattlePairWidget* findBeatenPair(QPoint);
    BattlePairWidget* findPairOfID(qint16);

    void playerMoveCard(Card*, QPoint);
    void cardLeaveWidget();
    void playerRaisedCard(Card*);
    void playerLoweredCard(Card*);

protected:
    void setPairsPosition();
    virtual void paintEvent(QPaintEvent*) override;
};
#endif // BATTLEAREAWIDGET_H
