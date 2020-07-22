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

    BattlePairWidget* m_targetPair;
    BattlePairWidget* m_trancferablePair;
public:
    explicit BattleAreaWidget(QWidget* parent);
    qint16 countOfPairs() const { return m_pairsList.size(); }


    BattlePairWidget* addNewPair();

    bool checkRightTossingCard();
    void tossCard(Card*);

    bool checkRightBeatingCard(QPoint);
    void beatCard(Card*, PairID);

    bool checkRightTrancferableCard();
    void trancferableCard(Card*);

    QList<Card*> endOfMove();





    void playerRaisedCard(bool);
    void playerLoweredCard();

    void playerMoveCard(Card*, QPoint);
    void cardLeaveWidget();



    BattlePairWidget* findBeatenPairOfCoordinates(QPoint);
    BattlePairWidget* findBeatenPairOfID(PairID);
protected:
    void setPairsPosition();
    virtual void paintEvent(QPaintEvent*) override;
};
#endif // BATTLEAREAWIDGET_H
