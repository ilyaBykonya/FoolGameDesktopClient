#ifndef BATTLEAREAWIDGET_H
#define BATTLEAREAWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../../GUIpart/BattlePair/BattlePairWidget.h"


class BattleAreaWidget : public QWidget
{
    Q_OBJECT
private:
    QList<BattlePairWidget*> m_pairsList;
    QHBoxLayout* m_topLine;
    QHBoxLayout* m_bottomLine;
public:
    explicit BattleAreaWidget(QWidget* parent);

public slots:
    void tossCard(Card*);
    void beatCard(Card*, qint16);

    QList<Card*>&& endOfMove();

signals:
    void playerWantBeatThisCard(BattlePairWidget*);

protected:
    void setPairsPosition(BattlePairWidget* pair);
    virtual void paintEvent(QPaintEvent*) override;
};
#endif // BATTLEAREAWIDGET_H
