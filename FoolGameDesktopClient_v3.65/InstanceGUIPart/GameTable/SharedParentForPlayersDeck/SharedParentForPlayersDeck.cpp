#include "SharedParentForPlayersDeck.h"

SharedParentForPlayersDeck::SharedParentForPlayersDeck(UserID id, QWidget *parent)
    :QWidget{ parent },
     m_playerQueue{ QueueMove::Other },
     m_ID{ id }
    {
    }

void SharedParentForPlayersDeck::setQueue(QueueMove newQueue) { m_playerQueue = newQueue; this->update(); }
SharedParentForPlayersDeck::QueueMove SharedParentForPlayersDeck::queue() const { return m_playerQueue; }

quint32 SharedParentForPlayersDeck::id() const { return m_ID; }
