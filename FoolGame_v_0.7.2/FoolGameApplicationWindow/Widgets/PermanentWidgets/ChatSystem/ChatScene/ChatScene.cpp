#include "ChatScene.h"

ChatScene::ChatScene(QRect rect, QObject* parent)
    :QGraphicsScene(rect, parent),
     m_chatWidget{ new ChatWidget }
    {
        this->addWidget(m_chatWidget);
    }

void ChatScene::resizeAllScene(QSize newSize)
{
    this->setSceneRect(this->sceneRect().x(), this->sceneRect().y(), newSize.width(), newSize.height());
    m_chatWidget->resize(newSize);
}
