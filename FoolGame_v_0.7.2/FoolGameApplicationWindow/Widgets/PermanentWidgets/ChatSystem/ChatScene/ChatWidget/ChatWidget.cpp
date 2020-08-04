#include "ChatWidget.h"


ChatWidget::ChatWidget(QWidget* parent)
    :CustomTabWidget{ parent }
    {
        for(quint8 idCanal = 0; idCanal < Canal::MAX_CANAL; ++idCanal)
        {
            this->setObjectName(QString("Canal_%1").arg(idCanal));
            ChatWindow* tab = new ChatWindow(Canal(idCanal));
            this->addTab(tab, this->objectName());
            QObject::connect(tab, &ChatWindow::signalSendMessage, this, &ChatWidget::slotSendMessage, Qt::ConnectionType::UniqueConnection);
            m_tabsList.push_back(tab);
        }
    }


void ChatWidget::slotReceiveUserMessage(Canal chatCanal, quint32 /*userID*/, const QString& message)
{
    for(auto it = m_tabsList.begin(); it != m_tabsList.end(); ++it)
    {
        if((*it)->canal() == chatCanal)
        {
            (*it)->slotReceiveMessage(message);
            return;
        }
    }
}
void ChatWidget::slotReceiveServerMessage(const QString& message)
{
    for(auto it = m_tabsList.begin(); it != m_tabsList.end(); ++it)
    {
        (*it)->slotReceiveMessage(message);
    }
}


void ChatWidget::slotSendMessage(Canal chatCanal, const QString& message)
{
    emit this->signalSendMessage(chatCanal, message);
    this->update();
}
