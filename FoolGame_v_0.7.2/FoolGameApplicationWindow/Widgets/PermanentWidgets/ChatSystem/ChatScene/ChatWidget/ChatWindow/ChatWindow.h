#pragma once
#include "FoolGameApplicationWindow/Files/ChatCanals.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>

class ChatWindow : public QWidget
{
    Q_OBJECT

private:
    QTextEdit* m_messageScreen;
    QLineEdit* m_entryField;

    Canal m_canal;
public:
    explicit ChatWindow(Canal, QWidget* = nullptr);
    Canal canal() const;

public slots:
    void slotReceiveMessage(const QString&);



protected slots:
    void slotSendMessage();
signals:
    void signalSendMessage(Canal, const QString&);
};
