#ifndef CHATSCENE_H
#define CHATSCENE_H
#include <QGraphicsScene>
#include "ChatWidget/ChatWidget.h"
class ChatScene : public QGraphicsScene
{
    Q_OBJECT
private:
    ChatWidget* m_chatWidget;

public:
    ChatScene(QRect = QRect(), QObject* = nullptr);

    ChatWidget* chatWidget() { return m_chatWidget; }

public slots:
    void resizeAllScene(QSize);
};

#endif // CHATSCENE_H
