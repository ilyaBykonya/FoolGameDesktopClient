#ifndef BATTLEPAIRWIDGET_H
#define BATTLEPAIRWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "../Card/Card.h"

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
private:
    Card* m_firstCard;
    Card* m_secondCard;
    PairState m_state;

    qint16 m_ID;

    QPoint m_parentPosition;
public:
    explicit BattlePairWidget(QPoint, QWidget *parent);
    ~BattlePairWidget();

    QSize sizeHint() const override { return size() * 1.1; }

    qint16 id() const { return m_ID; }
    Card* firstCard() { return m_firstCard; }
    Card* secondCard() { return m_secondCard; }

    PairState state() const { return m_state; }

protected:
    virtual void paintEvent(QPaintEvent *event) override;

public slots:
    void tossOnThisPair(Card*);
    void beatThisPair(Card*);

protected slots:
    void tossOnThisPairSecondStep(Card*);
    void beatThisPairSecondStep(Card*);
};

#endif // BATTLEPAIRWIDGET_H
