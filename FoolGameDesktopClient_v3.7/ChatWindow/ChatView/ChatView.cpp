#include "ChatView.h"

ChatView::ChatView(QGraphicsScene* scene, QWidget* parent)
    :QGraphicsView(scene, parent)
    {
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    }

void ChatView::resizeEvent(QResizeEvent* event)
{
    emit this->signalViewWarResized(event->size());
    QGraphicsView::resizeEvent(event);
}
