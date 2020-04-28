#ifndef BATTLEPAIRWIDGET_H
#define BATTLEPAIRWIDGET_H

#include <QWidget>
#include "../../Card/Card.h"

class BattlePairWidget : public QWidget
{
    Q_OBJECT
private:
    enum PairState{ NotBeaten = 0, Beaten = 1 };
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

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

public slots:
    void beatThisPair(Card*);

signals:
    void clickToThisPair(BattlePairWidget*);
};

#endif // BATTLEPAIRWIDGET_H
