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

public:
    explicit BattleAreaWidget(Card::Suit, QWidget* parent);

    bool tossCard(Card*);
    bool beatCard(Card*, QPoint);

    QList<Card*> endOfMove();

    BattlePairWidget* findBeatenPair(QPoint);

public slots:
    void serverSlotTossCard(Card*);
    void serverSlotBeatCard(Card*, qint16);

protected:
    void setPairsPosition(BattlePairWidget*);
    virtual void paintEvent(QPaintEvent*) override;

signals:
    void tryToss(Card*);
    void tryBeat(Card*, qint16);

    void emitText(const QString&);
};
#endif // BATTLEAREAWIDGET_H
