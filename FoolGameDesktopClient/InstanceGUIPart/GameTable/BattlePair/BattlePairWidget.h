#ifndef BATTLEPAIRWIDGET_H
#define BATTLEPAIRWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "../Card/Card.h"

class BattlePairWidget : public QWidget
{
    Q_OBJECT
public:
    enum PairState{ NotBeaten = 0, Beaten = 1 };
private:
    Card* m_firstCard;
    Card* m_secondCard;
    PairState m_state;

    qint16 m_ID;
public:
    explicit BattlePairWidget(Card*, QWidget *parent);
    ~BattlePairWidget();

    QSize sizeHint() const override { return size() * 1.1; }

    qint16 id() const { return m_ID; }
    Card* firstCard() { return m_firstCard; }
    Card* secondCard() { return m_secondCard; }

    void wasMove();
    PairState state() const { return m_state; }

protected:
    virtual void paintEvent(QPaintEvent *event) override;

public slots:
    void beatThisPair(Card*);

protected slots:
    void beatThisPairSecondStep(Card*);
    void secondPartOfConstructor(Card*);
};

#endif // BATTLEPAIRWIDGET_H
