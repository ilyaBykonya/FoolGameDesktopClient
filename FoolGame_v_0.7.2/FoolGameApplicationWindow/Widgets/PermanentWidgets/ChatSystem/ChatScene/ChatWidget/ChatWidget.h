#pragma once
#include "FoolGameApplicationWindow/Widgets/PermanentWidgets/CustomTabWidget/CustomTabWidget.h"
#include "ChatWindow/ChatWindow.h"
#include <QMessageBox>

class ChatWidget: public CustomTabWidget
{
    Q_OBJECT
private:
    QList<ChatWindow*> m_tabsList;

public:
    explicit ChatWidget(QWidget *parent = nullptr);

protected slots:
    void slotSendMessage(Canal, const QString&);

public slots:
    void slotReceiveUserMessage(Canal, quint32, const QString&);
    void slotReceiveServerMessage(const QString&);

signals:
    void signalSendMessage(Canal, const QString&);
};
