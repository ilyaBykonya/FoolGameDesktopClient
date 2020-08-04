#pragma once
#include <QResizeEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
class ChatView : public QGraphicsView
{
    Q_OBJECT
public:
    ChatView(QGraphicsScene*, QWidget* = nullptr);

protected slots:
    virtual void resizeEvent(QResizeEvent*) override;

signals:
    void signalViewWarResized(QSize);
};
