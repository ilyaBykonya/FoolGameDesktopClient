#include "SharedParentForPlayersDeck.h"

SharedParentForPlayersDeck::SharedParentForPlayersDeck(qint16 id, QWidget *parent)
    :QWidget{ parent },
     m_ID{ id }
    {
    }

void SharedParentForPlayersDeck::setQueue(QueueMove newQueue) { m_playerQueue = newQueue; this->repaint(); }
QueueMove SharedParentForPlayersDeck::queue() const { return m_playerQueue; }

qint16 SharedParentForPlayersDeck::id() const { return m_ID; }
