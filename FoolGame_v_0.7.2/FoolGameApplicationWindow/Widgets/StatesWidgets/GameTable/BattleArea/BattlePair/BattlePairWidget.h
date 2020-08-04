#ifndef BATTLEPAIRWIDGET_H
#define BATTLEPAIRWIDGET_H
#include <QGraphicsDropShadowEffect>
#include "../../Card/Card.h"
#include <QHBoxLayout>

class BattlePairWidget : public QWidget
{
    Q_OBJECT
public:
    enum PairState
    {
        Empty = 0,
        NotBeaten,
        Beaten
    };
    enum TargetState
    {
        NotTarget = 0,
        Target
    };

private:
    Card* m_firstCard;
    Card* m_secondCard;


    PairState m_pairState;
    TargetState m_pairTarget;

    PairID m_pairID;

    //нужно для анимации карт
    QPoint m_parentPosition;

    //тень по краю пары
    QGraphicsDropShadowEffect* m_graphicsEffect;
    QColor m_shadowColor;

public:
    explicit BattlePairWidget(QPoint, QWidget *parent);
    ~BattlePairWidget();

    virtual QSize sizeHint() const override;


    PairID pairID() const;
    Card* firstCard();
    Card* secondCard();


    PairState state() const;
    void setTargetState(TargetState);

protected slots:
    virtual void paintEvent(QPaintEvent*) override;

protected:
    void setPairState(PairState);

public slots:
    void tossOnThisPair(Card*);
    void beatThisPair(Card*);

protected slots:
    void tossOnThisPairSecondStep(Card*);
    void beatThisPairSecondStep(Card*);
};

#endif // BATTLEPAIRWIDGET_H
