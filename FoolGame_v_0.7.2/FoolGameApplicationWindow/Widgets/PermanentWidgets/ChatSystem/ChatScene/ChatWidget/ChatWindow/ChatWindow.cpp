#include "ChatWindow.h"



ChatWindow::ChatWindow(Canal chatCanal, QWidget* parent)
    :QWidget{ parent },
     m_messageScreen{ new QTextEdit },
     m_entryField{ new QLineEdit },
     m_canal{ chatCanal }
    {
        //ограничение в 50 строк
        m_messageScreen->document()->setMaximumBlockCount(50);


        m_messageScreen->setReadOnly(true);
        m_entryField->setPlaceholderText("message...");

        QVBoxLayout* layout = new QVBoxLayout;
            layout->setSpacing(0);
            layout->setMargin(0);

            layout->addWidget(m_messageScreen);
            layout->addWidget(m_entryField);
        this->setLayout(layout);
        QObject::connect(m_entryField, &QLineEdit::returnPressed, this, &ChatWindow::slotSendMessage, Qt::ConnectionType::UniqueConnection);
    }

Canal ChatWindow::canal() const
{
    return m_canal;
}



void ChatWindow::slotReceiveMessage(const QString& message)
{
    m_messageScreen->append(message);
}
void ChatWindow::slotSendMessage()
{
    emit this->signalSendMessage(m_canal, m_entryField->text());
    m_entryField->clear();
}

