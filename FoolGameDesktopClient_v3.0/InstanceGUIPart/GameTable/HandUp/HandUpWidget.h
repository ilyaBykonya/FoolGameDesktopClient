#ifndef HANDUPWIDGET_H
#define HANDUPWIDGET_H



#include <QtWidgets>
#include "../Card/Card.h"

class HandUpWidget : public QWidget
{
    Q_OBJECT
private:
    int m_countOfCards;
    QPixmap m_shirtCardPixmap;

public:
    explicit HandUpWidget(QWidget *parent = nullptr);

public slots:
    void putCard(Card* card);

protected:
    virtual void paintEvent(QPaintEvent*) override;

};

#endif // HANDUPWIDGET_H
