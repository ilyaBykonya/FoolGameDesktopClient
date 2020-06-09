#include "ChatWindow.h"

ChatWindow::ChatWindow(Canal canal, QWidget *parent)
    :QFrame{ parent },
     m_messageScreen{ new QTextEdit },
     m_entryField{ new QLineEdit },
     m_chatCanal{ canal }
    {
        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(m_messageScreen);
        layout->addWidget(m_entryField);
        this->setLayout(layout);

        m_messageScreen->setReadOnly(true);
        QObject::connect(m_entryField, &QLineEdit::returnPressed, this, &ChatWindow::slotSendMessage);
        this->setFrameStyle(QFrame::Shape::Panel | QFrame::Shadow::Plain);
        this->setFont(QFont("Times New Roman", 9, 3));
    }

void ChatWindow::slotReceiveMessage(Canal canal, const QString& message)
{
    if(canal != m_chatCanal)
        return;

    m_messageScreen->append(message);
}

void ChatWindow::slotSendMessage()
{
    emit this->signalSendMessage(m_chatCanal, m_entryField->text());
    m_entryField->clear();
}
