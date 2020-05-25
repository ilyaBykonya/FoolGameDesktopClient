#ifndef BATTLEAREAWIDGET_H
#define BATTLEAREAWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../BattlePair/BattlePairWidget.h"



class BattleAreaWidget : public QWidget
{
    Q_OBJECT
private:
    QList<BattlePairWidget*> m_pairsList;
    QHBoxLayout* m_topLine;
    QHBoxLayout* m_bottomLine;
    Card::Suit m_trump;

    QPoint m_thisRealPos;
public:
    explicit BattleAreaWidget(QPoint, Card::Suit, QWidget* parent);

    BattlePairWidget* addNewPair();

    BattlePairWidget* checkRightTossingCard(Card*);
    bool tossCard(Card*);

    BattlePairWidget* checkRightBeatingCard(Card*, QPoint);
    bool beatCard(Card*, qint16);


    QList<Card*> endOfMove();

    BattlePairWidget* findBeatenPair(QPoint);

protected:
    BattlePairWidget* setPairsPosition(BattlePairWidget*);
    virtual void paintEvent(QPaintEvent*) override;
};
#endif // BATTLEAREAWIDGET_H
