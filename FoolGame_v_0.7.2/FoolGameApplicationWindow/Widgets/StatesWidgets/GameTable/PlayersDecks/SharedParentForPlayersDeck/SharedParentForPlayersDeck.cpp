#include "SharedParentForPlayersDeck.h"


SharedPlayersDeckParent::SharedPlayersDeckParent(GameUserInformation* userInfo, QWidget *parent)
    :QWidget{ parent },
     m_userInfo{ userInfo },
     m_playerQueue{ QueueMove::Other }
    {
        m_userInfo->setParent(this);
    }

void SharedPlayersDeckParent::setQueue(QueueMove newQueue)
{
    m_playerQueue = newQueue; this->update();
}
SharedPlayersDeckParent::QueueMove SharedPlayersDeckParent::queue() const
{
    return m_playerQueue;
}

GameUserInformation* SharedPlayersDeckParent::user() const
{
    return m_userInfo;
}
