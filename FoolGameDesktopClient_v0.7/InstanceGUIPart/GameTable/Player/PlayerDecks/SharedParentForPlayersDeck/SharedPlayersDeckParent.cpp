#include "SharedPlayersDeckParent.h"

SharedPlayersDeckParent::SharedPlayersDeckParent(UserID id, const QString& name, QWidget *parent)
    :QWidget{ parent },
     m_playerQueue{ QueueMove::Other },
     m_user{ new ShowUserInfoWidget(id, name, this) }
    {
    }

void SharedPlayersDeckParent::setQueue(QueueMove newQueue) { m_playerQueue = newQueue; this->update(); }
SharedPlayersDeckParent::QueueMove SharedPlayersDeckParent::queue() const { return m_playerQueue; }
ShowUserInfoWidget* SharedPlayersDeckParent::user() { return m_user; }
