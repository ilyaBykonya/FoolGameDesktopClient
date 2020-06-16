#ifndef CHATWIDGET_H
#define CHATWIDGET_H
#include "ChatWindow/ChatWindow.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include "CustomTabWidget/CustomTabWidget.h"
#include "CanalsList.h"
#include <QMessageBox>
class ChatWidget : public CustomTabWidget
{
    Q_OBJECT
private:
    quint8 m_ID;


    QList<ChatWindow*> m_tabsList;
public:
    explicit ChatWidget(QWidget *parent = nullptr);

protected slots:
    void slotSendMessage(Canal, const QString&);

public slots:
    void slotReceiveUserMessage(Canal, quint16, const QString&);
    void slotReceiveServerMessage(const QString&);

signals:
    void signalSendMessage(Canal, const QString&);
};

#endif // CHATWINDOW_H
